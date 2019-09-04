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
struct TYPE_3__ {double b0; int b1; double b2; int b3; double b4; int a0; int a1; double a2; int a3; double a4; } ;
typedef  TYPE_1__ FoSection ;

/* Variables and functions */

__attribute__((used)) static void butterworth_fo_section(FoSection *S, double beta,
                                   double si, double g, double g0,
                                   double D, double c0)
{
    if (c0 == 1 || c0 == -1) {
        S->b0 = (g*g*beta*beta + 2*g*g0*si*beta + g0*g0)/D;
        S->b1 = 2*c0*(g*g*beta*beta - g0*g0)/D;
        S->b2 = (g*g*beta*beta - 2*g0*g*beta*si + g0*g0)/D;
        S->b3 = 0;
        S->b4 = 0;

        S->a0 = 1;
        S->a1 = 2*c0*(beta*beta - 1)/D;
        S->a2 = (beta*beta - 2*beta*si + 1)/D;
        S->a3 = 0;
        S->a4 = 0;
    } else {
        S->b0 = (g*g*beta*beta + 2*g*g0*si*beta + g0*g0)/D;
        S->b1 = -4*c0*(g0*g0 + g*g0*si*beta)/D;
        S->b2 = 2*(g0*g0*(1 + 2*c0*c0) - g*g*beta*beta)/D;
        S->b3 = -4*c0*(g0*g0 - g*g0*si*beta)/D;
        S->b4 = (g*g*beta*beta - 2*g*g0*si*beta + g0*g0)/D;

        S->a0 = 1;
        S->a1 = -4*c0*(1 + si*beta)/D;
        S->a2 = 2*(1 + 2*c0*c0 - beta*beta)/D;
        S->a3 = -4*c0*(1 - si*beta)/D;
        S->a4 = (beta*beta - 2*si*beta + 1)/D;
    }
}