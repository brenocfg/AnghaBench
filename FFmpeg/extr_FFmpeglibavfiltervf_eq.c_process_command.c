#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  gamma_weight_pexpr; int /*<<< orphan*/  gamma_b_pexpr; int /*<<< orphan*/  gamma_g_pexpr; int /*<<< orphan*/  gamma_r_pexpr; int /*<<< orphan*/  gamma_pexpr; int /*<<< orphan*/  saturation_pexpr; int /*<<< orphan*/  brightness_pexpr; int /*<<< orphan*/  contrast_pexpr; } ;
typedef  TYPE_1__ EQContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  set_brightness ; 
 int /*<<< orphan*/  set_contrast ; 
 int /*<<< orphan*/  set_gamma ; 
 int set_param (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_saturation ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    EQContext *eq = ctx->priv;

#define SET_PARAM(param_name, set_fn_name)                              \
    if (!strcmp(cmd, #param_name)) return set_param(&eq->param_name##_pexpr, args, cmd, set_##set_fn_name, ctx);

         SET_PARAM(contrast, contrast)
    else SET_PARAM(brightness, brightness)
    else SET_PARAM(saturation, saturation)
    else SET_PARAM(gamma, gamma)
    else SET_PARAM(gamma_r, gamma)
    else SET_PARAM(gamma_g, gamma)
    else SET_PARAM(gamma_b, gamma)
    else SET_PARAM(gamma_weight, gamma)
    else return AVERROR(ENOSYS);
}