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
struct TYPE_8__ {int /*<<< orphan*/  (* mdct_calc ) (TYPE_3__*,scalar_t__,scalar_t__) ;} ;
struct TYPE_7__ {float* buf; scalar_t__ in_buff; scalar_t__ mdct_out; TYPE_3__ mdct_ctx; TYPE_1__* fdsp; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* vector_fmul_reverse ) (scalar_t__,float*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* vector_fmul ) (scalar_t__,float*,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__ NellyMoserEncodeContext ;

/* Variables and functions */
 int NELLY_BUF_LEN ; 
 int /*<<< orphan*/  ff_sine_128 ; 
 int /*<<< orphan*/  stub1 (scalar_t__,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void apply_mdct(NellyMoserEncodeContext *s)
{
    float *in0 = s->buf;
    float *in1 = s->buf + NELLY_BUF_LEN;
    float *in2 = s->buf + 2 * NELLY_BUF_LEN;

    s->fdsp->vector_fmul        (s->in_buff,                 in0, ff_sine_128, NELLY_BUF_LEN);
    s->fdsp->vector_fmul_reverse(s->in_buff + NELLY_BUF_LEN, in1, ff_sine_128, NELLY_BUF_LEN);
    s->mdct_ctx.mdct_calc(&s->mdct_ctx, s->mdct_out, s->in_buff);

    s->fdsp->vector_fmul        (s->in_buff,                 in1, ff_sine_128, NELLY_BUF_LEN);
    s->fdsp->vector_fmul_reverse(s->in_buff + NELLY_BUF_LEN, in2, ff_sine_128, NELLY_BUF_LEN);
    s->mdct_ctx.mdct_calc(&s->mdct_ctx, s->mdct_out + NELLY_BUF_LEN, s->in_buff);
}