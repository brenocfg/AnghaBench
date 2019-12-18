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
struct TYPE_2__ {scalar_t__ name; int /*<<< orphan*/  minor; int /*<<< orphan*/ * fops; } ;
struct dlm_ls {TYPE_1__ ls_device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  device_fops ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int misc_register (TYPE_1__*) ; 
 char* name_prefix ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int dlm_device_register(struct dlm_ls *ls, char *name)
{
	int error, len;

	/* The device is already registered.  This happens when the
	   lockspace is created multiple times from userspace. */
	if (ls->ls_device.name)
		return 0;

	error = -ENOMEM;
	len = strlen(name) + strlen(name_prefix) + 2;
	ls->ls_device.name = kzalloc(len, GFP_NOFS);
	if (!ls->ls_device.name)
		goto fail;

	snprintf((char *)ls->ls_device.name, len, "%s_%s", name_prefix,
		 name);
	ls->ls_device.fops = &device_fops;
	ls->ls_device.minor = MISC_DYNAMIC_MINOR;

	error = misc_register(&ls->ls_device);
	if (error) {
		kfree(ls->ls_device.name);
	}
fail:
	return error;
}