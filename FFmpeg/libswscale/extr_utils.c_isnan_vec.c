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
struct TYPE_3__ {int length; int /*<<< orphan*/ * coeff; } ;
typedef  TYPE_1__ SwsVector ;

/* Variables and functions */
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isnan_vec(SwsVector *a)
{
    int i;
    for (i=0; i<a->length; i++)
        if (isnan(a->coeff[i]))
            return 1;
    return 0;
}