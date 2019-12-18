#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__* extended_data; } ;
struct TYPE_27__ {int /*<<< orphan*/  (* vector_fmul_scalar ) (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_26__ {scalar_t__* extended_data; } ;
struct TYPE_25__ {scalar_t__* extended_data; } ;
struct TYPE_24__ {scalar_t__* extended_data; } ;
struct TYPE_23__ {scalar_t__* extended_data; } ;
struct TYPE_22__ {scalar_t__* extended_data; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* fcmul_add ) (float*,float const*,float const*,int) ;} ;
struct TYPE_20__ {scalar_t__* extended_data; } ;
struct TYPE_19__ {TYPE_11__* priv; } ;
struct TYPE_18__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_17__ {int min_part_size; int nb_segments; int /*<<< orphan*/  wet_gain; TYPE_8__* fdsp; TYPE_2__ afirdsp; int /*<<< orphan*/  one2many; int /*<<< orphan*/  dry_gain; TYPE_10__* seg; TYPE_4__** in; } ;
struct TYPE_16__ {int input_offset; int* output_offset; int part_size; int input_size; int fft_length; int* part_index; int block_size; int nb_partitions; int coeff_size; TYPE_3__* buffer; int /*<<< orphan*/ * irdft; TYPE_1__* coeff; TYPE_9__* block; int /*<<< orphan*/ * rdft; TYPE_7__* sum; TYPE_6__* output; TYPE_5__* input; } ;
typedef  int /*<<< orphan*/  FFTComplex ;
typedef  TYPE_10__ AudioFIRSegment ;
typedef  TYPE_11__ AudioFIRContext ;
typedef  TYPE_12__ AVFrame ;
typedef  TYPE_13__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFALIGN (int const,int) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memmove (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (float*,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (float*,float const*,float const*,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fir_quantum(AVFilterContext *ctx, AVFrame *out, int ch, int offset)
{
    AudioFIRContext *s = ctx->priv;
    const float *in = (const float *)s->in[0]->extended_data[ch] + offset;
    float *block, *buf, *ptr = (float *)out->extended_data[ch] + offset;
    const int nb_samples = FFMIN(s->min_part_size, out->nb_samples - offset);
    int n, i, j;

    for (int segment = 0; segment < s->nb_segments; segment++) {
        AudioFIRSegment *seg = &s->seg[segment];
        float *src = (float *)seg->input->extended_data[ch];
        float *dst = (float *)seg->output->extended_data[ch];
        float *sum = (float *)seg->sum->extended_data[ch];

        s->fdsp->vector_fmul_scalar(src + seg->input_offset, in, s->dry_gain, FFALIGN(nb_samples, 4));
        emms_c();

        seg->output_offset[ch] += s->min_part_size;
        if (seg->output_offset[ch] == seg->part_size) {
            seg->output_offset[ch] = 0;
        } else {
            memmove(src, src + s->min_part_size, (seg->input_size - s->min_part_size) * sizeof(*src));

            dst += seg->output_offset[ch];
            for (n = 0; n < nb_samples; n++) {
                ptr[n] += dst[n];
            }
            continue;
        }

        memset(sum, 0, sizeof(*sum) * seg->fft_length);
        block = (float *)seg->block->extended_data[ch] + seg->part_index[ch] * seg->block_size;
        memset(block + seg->part_size, 0, sizeof(*block) * (seg->fft_length - seg->part_size));

        memcpy(block, src, sizeof(*src) * seg->part_size);

        av_rdft_calc(seg->rdft[ch], block);
        block[2 * seg->part_size] = block[1];
        block[1] = 0;

        j = seg->part_index[ch];

        for (i = 0; i < seg->nb_partitions; i++) {
            const int coffset = j * seg->coeff_size;
            const float *block = (const float *)seg->block->extended_data[ch] + i * seg->block_size;
            const FFTComplex *coeff = (const FFTComplex *)seg->coeff->extended_data[ch * !s->one2many] + coffset;

            s->afirdsp.fcmul_add(sum, block, (const float *)coeff, seg->part_size);

            if (j == 0)
                j = seg->nb_partitions;
            j--;
        }

        sum[1] = sum[2 * seg->part_size];
        av_rdft_calc(seg->irdft[ch], sum);

        buf = (float *)seg->buffer->extended_data[ch];
        for (n = 0; n < seg->part_size; n++) {
            buf[n] += sum[n];
        }

        memcpy(dst, buf, seg->part_size * sizeof(*dst));

        buf = (float *)seg->buffer->extended_data[ch];
        memcpy(buf, sum + seg->part_size, seg->part_size * sizeof(*buf));

        seg->part_index[ch] = (seg->part_index[ch] + 1) % seg->nb_partitions;

        memmove(src, src + s->min_part_size, (seg->input_size - s->min_part_size) * sizeof(*src));

        for (n = 0; n < nb_samples; n++) {
            ptr[n] += dst[n];
        }
    }

    s->fdsp->vector_fmul_scalar(ptr, ptr, s->wet_gain, FFALIGN(nb_samples, 4));
    emms_c();

    return 0;
}