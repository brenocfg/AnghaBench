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
struct TYPE_2__ {scalar_t__ img; } ;
struct iwl_drv {TYPE_1__ fw; } ;

/* Variables and functions */
 int IWL_UCODE_TYPE_MAX ; 
 int /*<<< orphan*/  iwl_free_fw_img (struct iwl_drv*,scalar_t__) ; 

__attribute__((used)) static void iwl_dealloc_ucode(struct iwl_drv *drv)
{
	int i;
	for (i = 0; i < IWL_UCODE_TYPE_MAX; i++)
		iwl_free_fw_img(drv, drv->fw.img + i);
}