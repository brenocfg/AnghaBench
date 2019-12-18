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
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void virtio_pci_release_dev(struct device *_d)
{
	/*
	 * No need for a release method as we allocate/free
	 * all devices together with the pci devices.
	 * Provide an empty one to avoid getting a warning from core.
	 */
}