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
typedef  int /*<<< orphan*/  SECURE_DEVICE ;

/* Variables and functions */

bool IsDeviceSupported(SECURE_DEVICE *dev)
{
	bool b = false;
#ifdef	OS_WIN32
	b = Win32IsDeviceSupported(dev);
#endif	// OS_WIN32
	return b;
}