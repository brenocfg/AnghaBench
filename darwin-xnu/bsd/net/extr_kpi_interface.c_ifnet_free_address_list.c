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
typedef  int /*<<< orphan*/ * ifaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFA_REMREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_TEMP ; 

void
ifnet_free_address_list(ifaddr_t *addresses)
{
	int i;

	if (addresses == NULL)
		return;

	for (i = 0; addresses[i] != NULL; i++)
		IFA_REMREF(addresses[i]);

	FREE(addresses, M_TEMP);
}