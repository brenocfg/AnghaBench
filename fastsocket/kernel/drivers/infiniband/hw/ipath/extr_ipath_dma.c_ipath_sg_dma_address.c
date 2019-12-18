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
typedef  scalar_t__ u64 ;
struct scatterlist {scalar_t__ offset; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static u64 ipath_sg_dma_address(struct ib_device *dev, struct scatterlist *sg)
{
	u64 addr = (u64) page_address(sg_page(sg));

	if (addr)
		addr += sg->offset;
	return addr;
}