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
typedef  scalar_t__ u32 ;
struct gss_api_mech {int gm_pf_num; TYPE_1__* gm_pfs; } ;
struct TYPE_2__ {scalar_t__ pseudoflavor; scalar_t__ service; } ;

/* Variables and functions */

u32
gss_pseudoflavor_to_service(struct gss_api_mech *gm, u32 pseudoflavor)
{
	int i;

	for (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].pseudoflavor == pseudoflavor)
			return gm->gm_pfs[i].service;
	}
	return 0;
}