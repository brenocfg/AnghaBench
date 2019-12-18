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
struct netxen_adapter {int /*<<< orphan*/ * fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

void
netxen_release_firmware(struct netxen_adapter *adapter)
{
	release_firmware(adapter->fw);
	adapter->fw = NULL;
}