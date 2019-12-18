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
struct TYPE_6__ {int /*<<< orphan*/ * process; } ;
struct TYPE_5__ {double contrast; double brightness; double gamma; int /*<<< orphan*/ * adjust; } ;
typedef  TYPE_1__ EQParameters ;
typedef  TYPE_2__ EQContext ;

/* Variables and functions */
 int /*<<< orphan*/ * apply_lut ; 
 double fabs (double) ; 

__attribute__((used)) static void check_values(EQParameters *param, EQContext *eq)
{
    if (param->contrast == 1.0 && param->brightness == 0.0 && param->gamma == 1.0)
        param->adjust = NULL;
    else if (param->gamma == 1.0 && fabs(param->contrast) < 7.9)
        param->adjust = eq->process;
    else
        param->adjust = apply_lut;
}