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
struct TYPE_3__ {int length; scalar_t__* coeff; } ;
typedef  TYPE_1__ SwsVector ;

/* Variables and functions */

__attribute__((used)) static double sws_dcVec(SwsVector *a)
{
    int i;
    double sum = 0;

    for (i = 0; i < a->length; i++)
        sum += a->coeff[i];

    return sum;
}