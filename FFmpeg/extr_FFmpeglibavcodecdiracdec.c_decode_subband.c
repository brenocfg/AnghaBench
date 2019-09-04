#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int num_x; int num_y; scalar_t__ pshift; int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {int width; int height; int stride; int /*<<< orphan*/ * ibuf; } ;
typedef  TYPE_1__ SubBand ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ DiracContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DIRAC_MAX_QUANT_INDEX ; 
 int /*<<< orphan*/  PARSE_VALUES (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int* ff_dirac_qoffset_intra_tab ; 
 int* ff_dirac_qscale_tab ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int16_t ; 
 int /*<<< orphan*/  int32_t ; 

__attribute__((used)) static void decode_subband(DiracContext *s, GetBitContext *gb, int quant,
                           int slice_x, int slice_y, int bits_end,
                           SubBand *b1, SubBand *b2)
{
    int left   = b1->width  * slice_x    / s->num_x;
    int right  = b1->width  *(slice_x+1) / s->num_x;
    int top    = b1->height * slice_y    / s->num_y;
    int bottom = b1->height *(slice_y+1) / s->num_y;

    int qfactor, qoffset;

    uint8_t *buf1 =      b1->ibuf + top * b1->stride;
    uint8_t *buf2 = b2 ? b2->ibuf + top * b2->stride: NULL;
    int x, y;

    if (quant > (DIRAC_MAX_QUANT_INDEX - 1)) {
        av_log(s->avctx, AV_LOG_ERROR, "Unsupported quant %d\n", quant);
        return;
    }
    qfactor = ff_dirac_qscale_tab[quant];
    qoffset = ff_dirac_qoffset_intra_tab[quant] + 2;
    /* we have to constantly check for overread since the spec explicitly
       requires this, with the meaning that all remaining coeffs are set to 0 */
    if (get_bits_count(gb) >= bits_end)
        return;

    if (s->pshift) {
        for (y = top; y < bottom; y++) {
            for (x = left; x < right; x++) {
                PARSE_VALUES(int32_t, x, gb, bits_end, buf1, buf2);
            }
            buf1 += b1->stride;
            if (buf2)
                buf2 += b2->stride;
        }
    }
    else {
        for (y = top; y < bottom; y++) {
            for (x = left; x < right; x++) {
                PARSE_VALUES(int16_t, x, gb, bits_end, buf1, buf2);
            }
            buf1 += b1->stride;
            if (buf2)
                buf2 += b2->stride;
        }
    }
}