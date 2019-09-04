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
typedef  int /*<<< orphan*/  zone_t ;
typedef  scalar_t__ vm_offset_t ;
struct zone_page_metadata {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  is_sane_zone_ptr (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static inline boolean_t
is_sane_zone_page_metadata(zone_t 	zone,
			   vm_offset_t 	page_meta)
{
	/* NULL page metadata structures are invalid */
	if (page_meta == 0)
		return FALSE;
	return is_sane_zone_ptr(zone, page_meta, sizeof(struct zone_page_metadata));
}