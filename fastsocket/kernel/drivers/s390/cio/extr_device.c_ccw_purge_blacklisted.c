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
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*) ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_bus_type ; 
 int /*<<< orphan*/  purge_fn ; 

int ccw_purge_blacklisted(void)
{
	CIO_MSG_EVENT(2, "ccw: purging blacklisted devices\n");
	bus_for_each_dev(&ccw_bus_type, NULL, NULL, purge_fn);
	return 0;
}