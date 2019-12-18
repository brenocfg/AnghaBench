#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AGP_PAGE_DESTROY_UNMAP ; 
 int ALI_CACHE_FLUSH_ADDR_MASK ; 
 int /*<<< orphan*/  ALI_CACHE_FLUSH_CTRL ; 
 int ALI_CACHE_FLUSH_EN ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  agp_generic_destroy_page (struct page*,int) ; 
 int /*<<< orphan*/  global_cache_flush () ; 
 int page_to_phys (struct page*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void m1541_destroy_page(struct page *page, int flags)
{
	u32 temp;

	if (page == NULL)
		return;

	if (flags & AGP_PAGE_DESTROY_UNMAP) {
		global_cache_flush();

		pci_read_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL, &temp);
		pci_write_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL,
				       (((temp & ALI_CACHE_FLUSH_ADDR_MASK) |
					 page_to_phys(page)) | ALI_CACHE_FLUSH_EN));
	}
	agp_generic_destroy_page(page, flags);
}