#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  enum dirac_subband { ____Placeholder_dirac_subband } dirac_subband ;
struct TYPE_20__ {scalar_t__ buffer; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* execute ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__**,int*,int,int) ;} ;
struct TYPE_18__ {int wavelet_depth; scalar_t__ is_arith; TYPE_1__* plane; TYPE_9__ gb; TYPE_4__* avctx; } ;
struct TYPE_17__ {int length; int quant; scalar_t__ coeff_data; } ;
struct TYPE_16__ {TYPE_2__*** band; } ;
typedef  TYPE_2__ SubBand ;
typedef  TYPE_3__ DiracContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DIRAC_MAX_QUANT_INDEX ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int MAX_DWT_LEVELS ; 
 int /*<<< orphan*/  align_get_bits (TYPE_9__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  decode_subband_arith ; 
 int /*<<< orphan*/  decode_subband_golomb ; 
 int get_bits_count (TYPE_9__*) ; 
 int get_bits_left (TYPE_9__*) ; 
 void* get_interleaved_ue_golomb (TYPE_9__*) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__**,int*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__**,int*,int,int) ; 

__attribute__((used)) static int decode_component(DiracContext *s, int comp)
{
    AVCodecContext *avctx = s->avctx;
    SubBand *bands[3*MAX_DWT_LEVELS+1];
    enum dirac_subband orientation;
    int level, num_bands = 0;
    int ret[3*MAX_DWT_LEVELS+1];
    int i;
    int damaged_count = 0;

    /* Unpack all subbands at all levels. */
    for (level = 0; level < s->wavelet_depth; level++) {
        for (orientation = !!level; orientation < 4; orientation++) {
            SubBand *b = &s->plane[comp].band[level][orientation];
            bands[num_bands++] = b;

            align_get_bits(&s->gb);
            /* [DIRAC_STD] 13.4.2 subband() */
            b->length = get_interleaved_ue_golomb(&s->gb);
            if (b->length) {
                b->quant = get_interleaved_ue_golomb(&s->gb);
                if (b->quant > (DIRAC_MAX_QUANT_INDEX - 1)) {
                    av_log(s->avctx, AV_LOG_ERROR, "Unsupported quant %d\n", b->quant);
                    b->quant = 0;
                    return AVERROR_INVALIDDATA;
                }
                align_get_bits(&s->gb);
                b->coeff_data = s->gb.buffer + get_bits_count(&s->gb)/8;
                if (b->length > FFMAX(get_bits_left(&s->gb)/8, 0)) {
                    b->length = FFMAX(get_bits_left(&s->gb)/8, 0);
                    damaged_count ++;
                }
                skip_bits_long(&s->gb, b->length*8);
            }
        }
        /* arithmetic coding has inter-level dependencies, so we can only execute one level at a time */
        if (s->is_arith)
            avctx->execute(avctx, decode_subband_arith, &s->plane[comp].band[level][!!level],
                           ret + 3*level + !!level, 4-!!level, sizeof(SubBand));
    }
    /* golomb coding has no inter-level dependencies, so we can execute all subbands in parallel */
    if (!s->is_arith)
        avctx->execute(avctx, decode_subband_golomb, bands, ret, num_bands, sizeof(SubBand*));

    for (i = 0; i < s->wavelet_depth * 3 + 1; i++) {
        if (ret[i] < 0)
            damaged_count++;
    }
    if (damaged_count > (s->wavelet_depth * 3 + 1) /2)
        return AVERROR_INVALIDDATA;

    return 0;
}