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
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * gamma_b_pexpr; int /*<<< orphan*/ * gamma_g_pexpr; int /*<<< orphan*/ * gamma_r_pexpr; int /*<<< orphan*/ * gamma_weight_pexpr; int /*<<< orphan*/ * gamma_pexpr; int /*<<< orphan*/ * saturation_pexpr; int /*<<< orphan*/ * brightness_pexpr; int /*<<< orphan*/ * contrast_pexpr; } ;
typedef  TYPE_1__ EQContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(AVFilterContext *ctx)
{
    EQContext *eq = ctx->priv;

    av_expr_free(eq->contrast_pexpr);     eq->contrast_pexpr     = NULL;
    av_expr_free(eq->brightness_pexpr);   eq->brightness_pexpr   = NULL;
    av_expr_free(eq->saturation_pexpr);   eq->saturation_pexpr   = NULL;
    av_expr_free(eq->gamma_pexpr);        eq->gamma_pexpr        = NULL;
    av_expr_free(eq->gamma_weight_pexpr); eq->gamma_weight_pexpr = NULL;
    av_expr_free(eq->gamma_r_pexpr);      eq->gamma_r_pexpr      = NULL;
    av_expr_free(eq->gamma_g_pexpr);      eq->gamma_g_pexpr      = NULL;
    av_expr_free(eq->gamma_b_pexpr);      eq->gamma_b_pexpr      = NULL;
}