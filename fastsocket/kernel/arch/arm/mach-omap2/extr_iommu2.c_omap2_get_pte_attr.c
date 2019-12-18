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
typedef  int u32 ;
struct iotlb_entry {int mixed; int endian; int elsz; int pgsz; } ;

/* Variables and functions */
 int MMU_CAM_PGSZ_4K ; 

__attribute__((used)) static u32 omap2_get_pte_attr(struct iotlb_entry *e)
{
	u32 attr;

	attr = e->mixed << 5;
	attr |= e->endian;
	attr |= e->elsz >> 3;
	attr <<= ((e->pgsz & MMU_CAM_PGSZ_4K) ? 0 : 6);

	return attr;
}