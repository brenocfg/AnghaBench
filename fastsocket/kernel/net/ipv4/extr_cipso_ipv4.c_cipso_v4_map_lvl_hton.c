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
typedef  size_t u32 ;
struct TYPE_6__ {TYPE_1__* std; } ;
struct cipso_v4_doi {int type; TYPE_3__ map; } ;
struct TYPE_5__ {size_t local_size; size_t* local; } ;
struct TYPE_4__ {TYPE_2__ lvl; } ;

/* Variables and functions */
 size_t CIPSO_V4_INV_LVL ; 
#define  CIPSO_V4_MAP_PASS 129 
#define  CIPSO_V4_MAP_TRANS 128 
 int EINVAL ; 
 int EPERM ; 

__attribute__((used)) static int cipso_v4_map_lvl_hton(const struct cipso_v4_doi *doi_def,
				 u32 host_lvl,
				 u32 *net_lvl)
{
	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		*net_lvl = host_lvl;
		return 0;
	case CIPSO_V4_MAP_TRANS:
		if (host_lvl < doi_def->map.std->lvl.local_size &&
		    doi_def->map.std->lvl.local[host_lvl] < CIPSO_V4_INV_LVL) {
			*net_lvl = doi_def->map.std->lvl.local[host_lvl];
			return 0;
		}
		return -EPERM;
	}

	return -EINVAL;
}