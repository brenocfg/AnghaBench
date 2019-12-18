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
struct agp_bridge_data {int dummy; } ;
struct _parisc_agp_info {int /*<<< orphan*/ * gatt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBA_AGPGART_COOKIE ; 
 struct _parisc_agp_info parisc_agp_info ; 

__attribute__((used)) static int
parisc_agp_free_gatt_table(struct agp_bridge_data *bridge)
{
	struct _parisc_agp_info *info = &parisc_agp_info;

	info->gatt[0] = SBA_AGPGART_COOKIE;

	return 0;
}