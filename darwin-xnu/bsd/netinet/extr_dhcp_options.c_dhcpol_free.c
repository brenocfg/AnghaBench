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
typedef  int /*<<< orphan*/  ptrlist_t ;
typedef  int /*<<< orphan*/  dhcpol_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptrlist_free (int /*<<< orphan*/ *) ; 

void
dhcpol_free(dhcpol_t * list)
{
    ptrlist_free((ptrlist_t *)list);
}