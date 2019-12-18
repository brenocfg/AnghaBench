#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  scalar_t__ buf ;
struct TYPE_15__ {int error; } ;
struct TYPE_14__ {int /*<<< orphan*/  num_refs; int /*<<< orphan*/  avctx; scalar_t__ old_delta_quant; scalar_t__ codeblock_mode; } ;
struct TYPE_13__ {int quant; int stride; scalar_t__ pshift; int /*<<< orphan*/ * ibuf; } ;
typedef  TYPE_1__ SubBand ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ DiracContext ;
typedef  TYPE_3__ DiracArith ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WN16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AV_WN32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CTX_DELTA_Q_DATA ; 
 int /*<<< orphan*/  CTX_DELTA_Q_F ; 
 int /*<<< orphan*/  CTX_ZERO_BLOCK ; 
 int DIRAC_MAX_QUANT_INDEX ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  coeff_unpack_arith_10 (TYPE_3__*,int,int,TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  coeff_unpack_arith_8 (TYPE_3__*,int,int,TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int coeff_unpack_golomb (int /*<<< orphan*/ *,int,int) ; 
 int dirac_get_arith_bit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int dirac_get_arith_int (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dirac_get_se_golomb (int /*<<< orphan*/ *) ; 
 int* ff_dirac_qoffset_inter_tab ; 
 int* ff_dirac_qoffset_intra_tab ; 
 int* ff_dirac_qscale_tab ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int codeblock(DiracContext *s, SubBand *b,
                             GetBitContext *gb, DiracArith *c,
                             int left, int right, int top, int bottom,
                             int blockcnt_one, int is_arith)
{
    int x, y, zero_block;
    int qoffset, qfactor;
    uint8_t *buf;

    /* check for any coded coefficients in this codeblock */
    if (!blockcnt_one) {
        if (is_arith)
            zero_block = dirac_get_arith_bit(c, CTX_ZERO_BLOCK);
        else
            zero_block = get_bits1(gb);

        if (zero_block)
            return 0;
    }

    if (s->codeblock_mode && !(s->old_delta_quant && blockcnt_one)) {
        int quant;
        if (is_arith)
            quant = dirac_get_arith_int(c, CTX_DELTA_Q_F, CTX_DELTA_Q_DATA);
        else
            quant = dirac_get_se_golomb(gb);
        if (quant > INT_MAX - b->quant || b->quant + quant < 0) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid quant\n");
            return AVERROR_INVALIDDATA;
        }
        b->quant += quant;
    }

    if (b->quant > (DIRAC_MAX_QUANT_INDEX - 1)) {
        av_log(s->avctx, AV_LOG_ERROR, "Unsupported quant %d\n", b->quant);
        b->quant = 0;
        return AVERROR_INVALIDDATA;
    }

    qfactor = ff_dirac_qscale_tab[b->quant];
    /* TODO: context pointer? */
    if (!s->num_refs)
        qoffset = ff_dirac_qoffset_intra_tab[b->quant] + 2;
    else
        qoffset = ff_dirac_qoffset_inter_tab[b->quant] + 2;

    buf = b->ibuf + top * b->stride;
    if (is_arith) {
        for (y = top; y < bottom; y++) {
            if (c->error)
                return c->error;
            for (x = left; x < right; x++) {
                if (b->pshift) {
                    coeff_unpack_arith_10(c, qfactor, qoffset, b, (int32_t*)(buf)+x, x, y);
                } else {
                    coeff_unpack_arith_8(c, qfactor, qoffset, b, (int16_t*)(buf)+x, x, y);
                }
            }
            buf += b->stride;
        }
    } else {
        for (y = top; y < bottom; y++) {
            if (get_bits_left(gb) < 1)
                return AVERROR_INVALIDDATA;
            for (x = left; x < right; x++) {
                int val = coeff_unpack_golomb(gb, qfactor, qoffset);
                if (b->pshift) {
                    AV_WN32(&buf[4*x], val);
                } else {
                    AV_WN16(&buf[2*x], val);
                }
            }
            buf += b->stride;
         }
     }
     return 0;
}