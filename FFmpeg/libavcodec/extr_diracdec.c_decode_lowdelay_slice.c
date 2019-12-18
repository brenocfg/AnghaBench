#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum dirac_subband { ____Placeholder_dirac_subband } dirac_subband ;
struct TYPE_12__ {TYPE_4__* priv_data; } ;
struct TYPE_8__ {scalar_t__** quant; } ;
struct TYPE_11__ {int wavelet_depth; TYPE_2__* plane; TYPE_1__ lowdelay; } ;
struct TYPE_10__ {int bytes; int /*<<< orphan*/  slice_y; int /*<<< orphan*/  slice_x; int /*<<< orphan*/  gb; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** band; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ DiracSlice ;
typedef  TYPE_4__ DiracContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  decode_subband (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_left (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_lowdelay_slice(AVCodecContext *avctx, void *arg)
{
    DiracContext *s = avctx->priv_data;
    DiracSlice *slice = arg;
    GetBitContext *gb = &slice->gb;
    enum dirac_subband orientation;
    int level, quant, chroma_bits, chroma_end;

    int quant_base  = get_bits(gb, 7); /*[DIRAC_STD] qindex */
    int length_bits = av_log2(8 * slice->bytes)+1;
    int luma_bits   = get_bits_long(gb, length_bits);
    int luma_end    = get_bits_count(gb) + FFMIN(luma_bits, get_bits_left(gb));

    /* [DIRAC_STD] 13.5.5.2 luma_slice_band */
    for (level = 0; level < s->wavelet_depth; level++)
        for (orientation = !!level; orientation < 4; orientation++) {
            quant = FFMAX(quant_base - s->lowdelay.quant[level][orientation], 0);
            decode_subband(s, gb, quant, slice->slice_x, slice->slice_y, luma_end,
                           &s->plane[0].band[level][orientation], NULL);
        }

    /* consume any unused bits from luma */
    skip_bits_long(gb, get_bits_count(gb) - luma_end);

    chroma_bits = 8*slice->bytes - 7 - length_bits - luma_bits;
    chroma_end  = get_bits_count(gb) + FFMIN(chroma_bits, get_bits_left(gb));
    /* [DIRAC_STD] 13.5.5.3 chroma_slice_band */
    for (level = 0; level < s->wavelet_depth; level++)
        for (orientation = !!level; orientation < 4; orientation++) {
            quant = FFMAX(quant_base - s->lowdelay.quant[level][orientation], 0);
            decode_subband(s, gb, quant, slice->slice_x, slice->slice_y, chroma_end,
                           &s->plane[1].band[level][orientation],
                           &s->plane[2].band[level][orientation]);
        }

    return 0;
}