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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (void*) ; 

void snmp_mib_free(void *ptr[2])
{
	BUG_ON(ptr == NULL);
	free_percpu(ptr[0]);
	free_percpu(ptr[1]);
	ptr[0] = ptr[1] = NULL;
}