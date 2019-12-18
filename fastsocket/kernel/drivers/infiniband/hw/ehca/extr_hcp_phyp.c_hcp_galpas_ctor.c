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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  fw_handle; } ;
struct TYPE_3__ {scalar_t__ fw_handle; } ;
struct h_galpas {TYPE_2__ user; TYPE_1__ kernel; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ hcall_map_page (int /*<<< orphan*/ ) ; 

int hcp_galpas_ctor(struct h_galpas *galpas, int is_user,
		    u64 paddr_kernel, u64 paddr_user)
{
	if (!is_user) {
		galpas->kernel.fw_handle = hcall_map_page(paddr_kernel);
		if (!galpas->kernel.fw_handle)
			return -ENOMEM;
	} else
		galpas->kernel.fw_handle = 0;

	galpas->user.fw_handle = paddr_user;

	return 0;
}