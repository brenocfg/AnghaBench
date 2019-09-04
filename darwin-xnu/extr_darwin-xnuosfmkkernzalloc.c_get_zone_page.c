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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct zone_page_metadata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_FOR_PAGE_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_INDEX_FOR_METADATA (struct zone_page_metadata*) ; 
 scalar_t__ from_zone_map (struct zone_page_metadata*,int) ; 
 int /*<<< orphan*/  trunc_page (struct zone_page_metadata*) ; 

__attribute__((used)) static inline vm_offset_t
get_zone_page(struct zone_page_metadata *page_meta)
{
	if (from_zone_map(page_meta, sizeof(struct zone_page_metadata)))
		return (vm_offset_t)(PAGE_FOR_PAGE_INDEX(PAGE_INDEX_FOR_METADATA(page_meta)));
	else
		return (vm_offset_t)(trunc_page(page_meta));
}