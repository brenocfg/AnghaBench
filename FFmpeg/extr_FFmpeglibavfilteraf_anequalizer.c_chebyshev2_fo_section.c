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

__attribute__((used)) static void chebyshev2_fo_section(FoSection *S, double a,
                                  double c, double tetta_b,
                                  double g, double si, double b,
                                  double D, double c0)
{
    if (c0 == 1 || c0 == -1) {
        S->b0 = (g*g*tetta_b*tetta_b + 2*tetta_b*g*b*si + b*b + g*g*c*c)/D;
        S->b1 = 2*c0*(g*g*tetta_b*tetta_b - b*b - g*g*c*c)/D;
        S->b2 = (g*g*tetta_b*tetta_b - 2*tetta_b*g*b*si + b*b + g*g*c*c)/D;
        S->b3 = 0;
        S->b4 = 0;

        S->a0 = 1;
        S->a1 = 2*c0*(tetta_b*tetta_b - a*a - c*c)/D;
        S->a2 = (tetta_b*tetta_b - 2*tetta_b*a*si + a*a + c*c)/D;
        S->a3 = 0;
        S->a4 = 0;
    } else {
        S->b0 = (g*g*tetta_b*tetta_b + 2*g*b*si*tetta_b + b*b + g*g*c*c)/D;
        S->b1 = -4*c0*(b*b + g*g*c*c + g*b*si*tetta_b)/D;
        S->b2 = 2*((b*b + g*g*c*c)*(1 + 2*c0*c0) - g*g*tetta_b*tetta_b)/D;
        S->b3 = -4*c0*(b*b + g*g*c*c - g*b*si*tetta_b)/D;
        S->b4 = (g*g*tetta_b*tetta_b - 2*g*b*si*tetta_b + b*b + g*g*c*c)/D;

        S->a0 = 1;
        S->a1 = -4*c0*(a*a + c*c + a*si*tetta_b)/D;
        S->a2 = 2*((a*a + c*c)*(1 + 2*c0*c0) - tetta_b*tetta_b)/D;
        S->a3 = -4*c0*(a*a + c*c - a*si*tetta_b)/D;
        S->a4 = (tetta_b*tetta_b - 2*a*si*tetta_b + a*a + c*c)/D;
    }
}