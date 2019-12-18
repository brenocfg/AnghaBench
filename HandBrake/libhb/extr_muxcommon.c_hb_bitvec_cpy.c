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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int size; int /*<<< orphan*/  vec; } ;
typedef  TYPE_1__ hb_bitvec_t ;

/* Variables and functions */
 int hb_bitvec_add_bits (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hb_bitvec_cpy(hb_bitvec_t *bv1, hb_bitvec_t *bv2)
{
    if (bv1->size < bv2->size)
    {
        int result = hb_bitvec_add_bits(bv1, bv2->size - bv1->size);
        if (result < 0)
            return result;
    }

    int words = (bv1->size + 31) >> 5;
    memcpy(bv1->vec, bv2->vec, words * sizeof(uint32_t));

    return 0;
}