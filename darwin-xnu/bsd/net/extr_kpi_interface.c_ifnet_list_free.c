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
typedef  scalar_t__ ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  ifnet_release (scalar_t__) ; 

void
ifnet_list_free(ifnet_t *interfaces)
{
	int i;

	if (interfaces == NULL)
		return;

	for (i = 0; interfaces[i]; i++)
		ifnet_release(interfaces[i]);

	FREE(interfaces, M_TEMP);
}