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
typedef  int /*<<< orphan*/  u64 ;
struct nouveau_vmmgr {int (* create ) (struct nouveau_vmmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_vm**) ;} ;
struct nouveau_vm {int dummy; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_vmmgr* nouveau_vmmgr (struct nouveau_device*) ; 
 int stub1 (struct nouveau_vmmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_vm**) ; 

int
nouveau_vm_new(struct nouveau_device *device, u64 offset, u64 length,
	       u64 mm_offset, struct nouveau_vm **pvm)
{
	struct nouveau_vmmgr *vmm = nouveau_vmmgr(device);
	return vmm->create(vmm, offset, length, mm_offset, pvm);
}