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
struct idr_layer {scalar_t__ bitmap; } ;

/* Variables and functions */
 int IDR_BITS ; 
 scalar_t__ IDR_FULL ; 
 int IDR_MASK ; 
 int /*<<< orphan*/  __set_bit (int,scalar_t__*) ; 

__attribute__((used)) static void idr_mark_full(struct idr_layer **pa, int id)
{
	struct idr_layer *p = pa[0];
	int l = 0;

	__set_bit(id & IDR_MASK, &p->bitmap);
	/*
	 * If this layer is full mark the bit in the layer above to
	 * show that this part of the radix tree is full.  This may
	 * complete the layer above and require walking up the radix
	 * tree.
	 */
	while (p->bitmap == IDR_FULL) {
		if (!(p = pa[++l]))
			break;
		id = id >> IDR_BITS;
		__set_bit((id & IDR_MASK), &p->bitmap);
	}
}