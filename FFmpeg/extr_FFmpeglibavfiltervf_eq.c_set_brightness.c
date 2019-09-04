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
struct TYPE_7__ {scalar_t__ lut_clean; int /*<<< orphan*/  brightness; } ;
struct TYPE_6__ {TYPE_3__* param; int /*<<< orphan*/  brightness; int /*<<< orphan*/  var_values; int /*<<< orphan*/  brightness_pexpr; } ;
typedef  TYPE_1__ EQContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_clipf (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  av_expr_eval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  check_values (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static void set_brightness(EQContext *eq)
{
    eq->brightness = av_clipf(av_expr_eval(eq->brightness_pexpr, eq->var_values, eq), -1.0, 1.0);
    eq->param[0].brightness = eq->brightness;
    eq->param[0].lut_clean = 0;
    check_values(&eq->param[0], eq);
}