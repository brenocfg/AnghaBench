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
typedef  int /*<<< orphan*/  SL_UNICODE ;
typedef  int /*<<< orphan*/  SL_DEVICE ;

/* Variables and functions */
 int /*<<< orphan*/  SlFreeUnicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SlNewDeviceUnicode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SlNewUnicode (char*) ; 

SL_DEVICE *SlNewDevice(char *device_name, char *symbolic_link_name)
{
	SL_UNICODE *u_device_name = SlNewUnicode(device_name);
	SL_UNICODE *u_sym_name = SlNewUnicode(symbolic_link_name);

	SL_DEVICE *ret = SlNewDeviceUnicode(u_device_name, u_sym_name);

	if (ret == NULL)
	{
		SlFreeUnicode(u_device_name);
		SlFreeUnicode(u_sym_name);
	}

	return ret;
}