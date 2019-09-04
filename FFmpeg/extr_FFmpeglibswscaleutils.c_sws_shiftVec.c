#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  length; struct TYPE_7__* coeff; } ;
typedef  TYPE_1__ SwsVector ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  makenan_vec (TYPE_1__*) ; 
 TYPE_1__* sws_getShiftedVec (TYPE_1__*,int) ; 

void sws_shiftVec(SwsVector *a, int shift)
{
    SwsVector *shifted = sws_getShiftedVec(a, shift);
    if (!shifted) {
        makenan_vec(a);
        return;
    }
    av_free(a->coeff);
    a->coeff  = shifted->coeff;
    a->length = shifted->length;
    av_free(shifted);
}