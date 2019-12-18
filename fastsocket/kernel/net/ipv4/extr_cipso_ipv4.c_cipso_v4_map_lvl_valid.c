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
typedef  size_t u8 ;
struct TYPE_6__ {TYPE_2__* std; } ;
struct cipso_v4_doi {int type; TYPE_3__ map; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cipso; } ;
struct TYPE_5__ {TYPE_1__ lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPSO_V4_INV_LVL ; 
#define  CIPSO_V4_MAP_PASS 129 
#define  CIPSO_V4_MAP_TRANS 128 
 int EFAULT ; 

__attribute__((used)) static int cipso_v4_map_lvl_valid(const struct cipso_v4_doi *doi_def, u8 level)
{
	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		return 0;
	case CIPSO_V4_MAP_TRANS:
		if (doi_def->map.std->lvl.cipso[level] < CIPSO_V4_INV_LVL)
			return 0;
		break;
	}

	return -EFAULT;
}