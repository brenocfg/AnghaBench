#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {size_t data_size; int j; scalar_t__ x; int /*<<< orphan*/  diff; scalar_t__ t; scalar_t__ err; scalar_t__ const* in_buf; } ;
typedef  TYPE_1__ ElsDecCtx ;

/* Variables and functions */
 scalar_t__ AV_RB16 (scalar_t__ const*) ; 
 scalar_t__ AV_RB24 (scalar_t__ const*) ; 
 int ELS_JOTS_PER_BYTE ; 
 scalar_t__ ELS_MAX ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,scalar_t__) ; 
 scalar_t__* els_exp_tab ; 

void ff_els_decoder_init(ElsDecCtx *ctx, const uint8_t *in, size_t data_size)
{
    int nbytes;

    /* consume up to 3 bytes from the input data */
    if (data_size >= 3) {
        ctx->x = AV_RB24(in);
        nbytes = 3;
    } else if (data_size == 2) {
        ctx->x = AV_RB16(in);
        nbytes = 2;
    } else {
        ctx->x = *in;
        nbytes = 1;
    }

    ctx->in_buf    = in + nbytes;
    ctx->data_size = data_size - nbytes;
    ctx->err       = 0;
    ctx->j         = ELS_JOTS_PER_BYTE;
    ctx->t         = ELS_MAX;
    ctx->diff      = FFMIN(ELS_MAX - ctx->x,
                           ELS_MAX - els_exp_tab[ELS_JOTS_PER_BYTE * 4 - 1]);
}