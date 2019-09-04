#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_8__ {int* adapt_pred_order; int highest_pred_order; int** msb_sample_buffer; int lsb_section_size; scalar_t__* nscalablelsbs; scalar_t__* lsb_sample_buffer; } ;
struct TYPE_7__ {int nchannels; int* bitalloc_hybrid_linear; int nabits; int* bitalloc_part_a; int* nsamples_part_a; int* bitalloc_part_b; int /*<<< orphan*/ ** deci_history; void** rice_code_flag; void* seg_common; TYPE_3__* bands; } ;
struct TYPE_6__ {int nsegsamples; int nsegsamples_log2; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  TYPE_2__ DCAXllChSet ;
typedef  TYPE_3__ DCAXllBand ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_XLL_DECI_HISTORY_MAX ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_array (int /*<<< orphan*/ *,scalar_t__,int,scalar_t__) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int get_linear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_linear_array (int /*<<< orphan*/ *,int*,int,int) ; 
 int get_rice (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_rice_array (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  get_sbits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int chs_parse_band_data(DCAXllDecoder *s, DCAXllChSet *c, int band, int seg, int band_data_end)
{
    DCAXllBand *b = &c->bands[band];
    int i, j, k;

    // Start unpacking MSB portion of the segment
    if (!(seg && get_bits1(&s->gb))) {
        // Unpack segment type
        // 0 - distinct coding parameters for each channel
        // 1 - common coding parameters for all channels
        c->seg_common = get_bits1(&s->gb);

        // Determine number of coding parameters encoded in segment
        k = c->seg_common ? 1 : c->nchannels;

        // Unpack Rice coding parameters
        for (i = 0; i < k; i++) {
            // Unpack Rice coding flag
            // 0 - linear code, 1 - Rice code
            c->rice_code_flag[i] = get_bits1(&s->gb);
            // Unpack Hybrid Rice coding flag
            // 0 - Rice code, 1 - Hybrid Rice code
            if (!c->seg_common && c->rice_code_flag[i] && get_bits1(&s->gb))
                // Unpack binary code length for isolated samples
                c->bitalloc_hybrid_linear[i] = get_bits(&s->gb, c->nabits) + 1;
            else
                // 0 indicates no Hybrid Rice coding
                c->bitalloc_hybrid_linear[i] = 0;
        }

        // Unpack coding parameters
        for (i = 0; i < k; i++) {
            if (seg == 0) {
                // Unpack coding parameter for part A of segment 0
                c->bitalloc_part_a[i] = get_bits(&s->gb, c->nabits);

                // Adjust for the linear code
                if (!c->rice_code_flag[i] && c->bitalloc_part_a[i])
                    c->bitalloc_part_a[i]++;

                if (!c->seg_common)
                    c->nsamples_part_a[i] = b->adapt_pred_order[i];
                else
                    c->nsamples_part_a[i] = b->highest_pred_order;
            } else {
                c->bitalloc_part_a[i] = 0;
                c->nsamples_part_a[i] = 0;
            }

            // Unpack coding parameter for part B of segment
            c->bitalloc_part_b[i] = get_bits(&s->gb, c->nabits);

            // Adjust for the linear code
            if (!c->rice_code_flag[i] && c->bitalloc_part_b[i])
                c->bitalloc_part_b[i]++;
        }
    }

    // Unpack entropy codes
    for (i = 0; i < c->nchannels; i++) {
        int32_t *part_a, *part_b;
        int nsamples_part_b;

        // Select index of coding parameters
        k = c->seg_common ? 0 : i;

        // Slice the segment into parts A and B
        part_a = b->msb_sample_buffer[i] + seg * s->nsegsamples;
        part_b = part_a + c->nsamples_part_a[k];
        nsamples_part_b = s->nsegsamples - c->nsamples_part_a[k];

        if (get_bits_left(&s->gb) < 0)
            return AVERROR_INVALIDDATA;

        if (!c->rice_code_flag[k]) {
            // Linear codes
            // Unpack all residuals of part A of segment 0
            get_linear_array(&s->gb, part_a, c->nsamples_part_a[k],
                             c->bitalloc_part_a[k]);

            // Unpack all residuals of part B of segment 0 and others
            get_linear_array(&s->gb, part_b, nsamples_part_b,
                             c->bitalloc_part_b[k]);
        } else {
            // Rice codes
            // Unpack all residuals of part A of segment 0
            get_rice_array(&s->gb, part_a, c->nsamples_part_a[k],
                           c->bitalloc_part_a[k]);

            if (c->bitalloc_hybrid_linear[k]) {
                // Hybrid Rice codes
                // Unpack the number of isolated samples
                int nisosamples = get_bits(&s->gb, s->nsegsamples_log2);

                // Set all locations to 0
                memset(part_b, 0, sizeof(*part_b) * nsamples_part_b);

                // Extract the locations of isolated samples and flag by -1
                for (j = 0; j < nisosamples; j++) {
                    int loc = get_bits(&s->gb, s->nsegsamples_log2);
                    if (loc >= nsamples_part_b) {
                        av_log(s->avctx, AV_LOG_ERROR, "Invalid isolated sample location\n");
                        return AVERROR_INVALIDDATA;
                    }
                    part_b[loc] = -1;
                }

                // Unpack all residuals of part B of segment 0 and others
                for (j = 0; j < nsamples_part_b; j++) {
                    if (part_b[j])
                        part_b[j] = get_linear(&s->gb, c->bitalloc_hybrid_linear[k]);
                    else
                        part_b[j] = get_rice(&s->gb, c->bitalloc_part_b[k]);
                }
            } else {
                // Rice codes
                // Unpack all residuals of part B of segment 0 and others
                get_rice_array(&s->gb, part_b, nsamples_part_b, c->bitalloc_part_b[k]);
            }
        }
    }

    // Unpack decimator history for frequency band 1
    if (seg == 0 && band == 1) {
        int nbits = get_bits(&s->gb, 5) + 1;
        for (i = 0; i < c->nchannels; i++)
            for (j = 1; j < DCA_XLL_DECI_HISTORY_MAX; j++)
                c->deci_history[i][j] = get_sbits_long(&s->gb, nbits);
    }

    // Start unpacking LSB portion of the segment
    if (b->lsb_section_size) {
        // Skip to the start of LSB portion
        if (ff_dca_seek_bits(&s->gb, band_data_end - b->lsb_section_size * 8)) {
            av_log(s->avctx, AV_LOG_ERROR, "Read past end of XLL band data\n");
            return AVERROR_INVALIDDATA;
        }

        // Unpack all LSB parts of residuals of this segment
        for (i = 0; i < c->nchannels; i++) {
            if (b->nscalablelsbs[i]) {
                get_array(&s->gb,
                          b->lsb_sample_buffer[i] + seg * s->nsegsamples,
                          s->nsegsamples, b->nscalablelsbs[i]);
            }
        }
    }

    // Skip to the end of band data
    if (ff_dca_seek_bits(&s->gb, band_data_end)) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of XLL band data\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}