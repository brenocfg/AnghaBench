#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int gamma; scalar_t__ lut_clean; void* gamma_weight; } ;
struct TYPE_6__ {int gamma; int gamma_r; int gamma_g; int gamma_b; TYPE_3__* param; void* gamma_weight; int /*<<< orphan*/  var_values; int /*<<< orphan*/  gamma_weight_pexpr; int /*<<< orphan*/  gamma_b_pexpr; int /*<<< orphan*/  gamma_g_pexpr; int /*<<< orphan*/  gamma_r_pexpr; int /*<<< orphan*/  gamma_pexpr; } ;
typedef  TYPE_1__ EQContext ;

/* Variables and functions */
 void* av_clipf (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  av_expr_eval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  check_values (TYPE_3__*,TYPE_1__*) ; 
 void* sqrt (int) ; 

__attribute__((used)) static void set_gamma(EQContext *eq)
{
    int i;

    eq->gamma        = av_clipf(av_expr_eval(eq->gamma_pexpr,        eq->var_values, eq), 0.1, 10.0);
    eq->gamma_r      = av_clipf(av_expr_eval(eq->gamma_r_pexpr,      eq->var_values, eq), 0.1, 10.0);
    eq->gamma_g      = av_clipf(av_expr_eval(eq->gamma_g_pexpr,      eq->var_values, eq), 0.1, 10.0);
    eq->gamma_b      = av_clipf(av_expr_eval(eq->gamma_b_pexpr,      eq->var_values, eq), 0.1, 10.0);
    eq->gamma_weight = av_clipf(av_expr_eval(eq->gamma_weight_pexpr, eq->var_values, eq), 0.0,  1.0);

    eq->param[0].gamma = eq->gamma * eq->gamma_g;
    eq->param[1].gamma = sqrt(eq->gamma_b / eq->gamma_g);
    eq->param[2].gamma = sqrt(eq->gamma_r / eq->gamma_g);

    for (i = 0; i < 3; i++) {
        eq->param[i].gamma_weight = eq->gamma_weight;
        eq->param[i].lut_clean = 0;
        check_values(&eq->param[i], eq);
    }
}