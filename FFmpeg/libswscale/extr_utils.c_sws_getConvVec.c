#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; int* coeff; } ;
typedef  TYPE_1__ SwsVector ;

/* Variables and functions */
 TYPE_1__* sws_getConstVec (double,int) ; 

__attribute__((used)) static SwsVector *sws_getConvVec(SwsVector *a, SwsVector *b)
{
    int length = a->length + b->length - 1;
    int i, j;
    SwsVector *vec = sws_getConstVec(0.0, length);

    if (!vec)
        return NULL;

    for (i = 0; i < a->length; i++) {
        for (j = 0; j < b->length; j++) {
            vec->coeff[i + j] += a->coeff[i] * b->coeff[j];
        }
    }

    return vec;
}