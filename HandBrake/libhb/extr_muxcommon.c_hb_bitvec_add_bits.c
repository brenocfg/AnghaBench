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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int size; scalar_t__* vec; } ;
typedef  TYPE_1__ hb_bitvec_t ;

/* Variables and functions */
 scalar_t__* realloc (scalar_t__*,int) ; 

__attribute__((used)) static int hb_bitvec_add_bits(hb_bitvec_t *bv, int bits)
{
    int ii;
    int words_cur = (bv->size + 31) >> 5;
    int words = (bv->size + bits + 31) >> 5;
    if (words > words_cur)
    {
        uint32_t *tmp = realloc(bv->vec, words * sizeof(uint32_t));
        if (tmp == NULL)
        {
            return -1;
        }
        for (ii = words_cur; ii < words; ii++)
            tmp[ii] = 0;
        bv->vec = tmp;
    }
    bv->size += bits;
    return 0;
}