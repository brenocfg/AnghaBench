#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; int /*<<< orphan*/ * coeff; } ;
typedef  TYPE_1__ SwsVector ;

/* Variables and functions */
 int FFABS (int) ; 
 TYPE_1__* sws_getConstVec (double,int) ; 

__attribute__((used)) static SwsVector *sws_getShiftedVec(SwsVector *a, int shift)
{
    int length = a->length + FFABS(shift) * 2;
    int i;
    SwsVector *vec = sws_getConstVec(0.0, length);

    if (!vec)
        return NULL;

    for (i = 0; i < a->length; i++) {
        vec->coeff[i + (length    - 1) / 2 -
                       (a->length - 1) / 2 - shift] = a->coeff[i];
    }

    return vec;
}