#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {scalar_t__ gtt; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_entry ) (int /*<<< orphan*/ ,int,unsigned int) ;} ;

/* Variables and functions */
 TYPE_2__ intel_private ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void intel_gtt_insert_pages(unsigned int first_entry,
				   unsigned int num_entries,
				   struct page **pages,
				   unsigned int flags)
{
	int i, j;

	for (i = 0, j = first_entry; i < num_entries; i++, j++) {
		dma_addr_t addr = page_to_phys(pages[i]);
		intel_private.driver->write_entry(addr,
						  j, flags);
	}
	readl(intel_private.gtt+j-1);
}