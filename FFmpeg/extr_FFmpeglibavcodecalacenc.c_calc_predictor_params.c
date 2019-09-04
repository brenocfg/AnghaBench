#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int compression_level; TYPE_1__* lpc; int /*<<< orphan*/  max_prediction_order; int /*<<< orphan*/  min_prediction_order; int /*<<< orphan*/  frame_size; int /*<<< orphan*/ * sample_buf; int /*<<< orphan*/  lpc_ctx; } ;
struct TYPE_4__ {int lpc_order; int lpc_quant; int* lpc_coeff; } ;
typedef  TYPE_2__ AlacEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALAC_MAX_LPC_PRECISION ; 
 int /*<<< orphan*/  ALAC_MAX_LPC_SHIFT ; 
 int /*<<< orphan*/  ALAC_MIN_LPC_SHIFT ; 
 int /*<<< orphan*/  FF_LPC_TYPE_LEVINSON ; 
 int MAX_LPC_ORDER ; 
 int /*<<< orphan*/  ORDER_METHOD_EST ; 
 int ff_lpc_calc_coefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void calc_predictor_params(AlacEncodeContext *s, int ch)
{
    int32_t coefs[MAX_LPC_ORDER][MAX_LPC_ORDER];
    int shift[MAX_LPC_ORDER];
    int opt_order;

    if (s->compression_level == 1) {
        s->lpc[ch].lpc_order = 6;
        s->lpc[ch].lpc_quant = 6;
        s->lpc[ch].lpc_coeff[0] =  160;
        s->lpc[ch].lpc_coeff[1] = -190;
        s->lpc[ch].lpc_coeff[2] =  170;
        s->lpc[ch].lpc_coeff[3] = -130;
        s->lpc[ch].lpc_coeff[4] =   80;
        s->lpc[ch].lpc_coeff[5] =  -25;
    } else {
        opt_order = ff_lpc_calc_coefs(&s->lpc_ctx, s->sample_buf[ch],
                                      s->frame_size,
                                      s->min_prediction_order,
                                      s->max_prediction_order,
                                      ALAC_MAX_LPC_PRECISION, coefs, shift,
                                      FF_LPC_TYPE_LEVINSON, 0,
                                      ORDER_METHOD_EST, ALAC_MIN_LPC_SHIFT,
                                      ALAC_MAX_LPC_SHIFT, 1);

        s->lpc[ch].lpc_order = opt_order;
        s->lpc[ch].lpc_quant = shift[opt_order-1];
        memcpy(s->lpc[ch].lpc_coeff, coefs[opt_order-1], opt_order*sizeof(int));
    }
}