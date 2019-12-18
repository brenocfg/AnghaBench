#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; scalar_t__* vec; } ;
typedef  TYPE_1__ hb_bitvec_t ;

/* Variables and functions */

__attribute__((used)) static int hb_bitvec_cmp(hb_bitvec_t *bv1, hb_bitvec_t *bv2)
{
    if (bv1->size != bv2->size)
        return 0;

    int ii;
    int words = (bv1->size + 31) >> 5;
    for (ii = 0; ii < words; ii++)
        if (bv1->vec[ii] != bv2->vec[ii])
            return 0;
    return 1;
}