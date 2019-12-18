#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ps3_dma_region {unsigned long offset; unsigned long len; unsigned long bus_addr; } ;
struct TYPE_5__ {scalar_t__ offset; } ;
struct TYPE_4__ {unsigned long size; } ;
struct TYPE_6__ {TYPE_2__ r1; TYPE_1__ rm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_3__ map ; 

__attribute__((used)) static unsigned long dma_sb_lpar_to_bus(struct ps3_dma_region *r,
	unsigned long lpar_addr)
{
	if (lpar_addr >= map.rm.size)
		lpar_addr -= map.r1.offset;
	BUG_ON(lpar_addr < r->offset);
	BUG_ON(lpar_addr >= r->offset + r->len);
	return r->bus_addr + lpar_addr - r->offset;
}