#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  hb_bitvec_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  hb_bitvec_add_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static hb_bitvec_t* hb_bitvec_new(int size)
{
    hb_bitvec_t *bv = calloc(sizeof(hb_bitvec_t), 1);
    hb_bitvec_add_bits(bv, size);
    return bv;
}