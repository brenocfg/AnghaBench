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
struct TYPE_4__ {scalar_t__ fw_handle; } ;
struct TYPE_3__ {scalar_t__ fw_handle; } ;
struct h_galpas {TYPE_2__ kernel; TYPE_1__ user; } ;

/* Variables and functions */
 int hcall_unmap_page (scalar_t__) ; 

int hcp_galpas_dtor(struct h_galpas *galpas)
{
	if (galpas->kernel.fw_handle) {
		int ret = hcall_unmap_page(galpas->kernel.fw_handle);
		if (ret)
			return ret;
	}

	galpas->user.fw_handle = galpas->kernel.fw_handle = 0;

	return 0;
}