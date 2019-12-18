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
struct TYPE_3__ {double b0; int b1; int* num; int* denum; int a1; int b2; int a2; int b3; int a3; int b4; int a4; } ;
typedef  TYPE_1__ FoSection ;

/* Variables and functions */

__attribute__((used)) static inline double section_process(FoSection *S, double in)
{
    double out;

    out = S->b0 * in;
    out+= S->b1 * S->num[0] - S->denum[0] * S->a1;
    out+= S->b2 * S->num[1] - S->denum[1] * S->a2;
    out+= S->b3 * S->num[2] - S->denum[2] * S->a3;
    out+= S->b4 * S->num[3] - S->denum[3] * S->a4;

    S->num[3] = S->num[2];
    S->num[2] = S->num[1];
    S->num[1] = S->num[0];
    S->num[0] = in;

    S->denum[3] = S->denum[2];
    S->denum[2] = S->denum[1];
    S->denum[1] = S->denum[0];
    S->denum[0] = out;

    return out;
}