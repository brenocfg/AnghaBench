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
typedef  int /*<<< orphan*/  u16 ;
struct ipath_portdata {int /*<<< orphan*/  port_pkeys; } ;
struct ipath_devdata {struct ipath_portdata** ipath_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_pkeys(struct ipath_devdata *dd, u16 * pkeys)
{
	/* always a kernel port, no locking needed */
	struct ipath_portdata *pd = dd->ipath_pd[0];

	memcpy(pkeys, pd->port_pkeys, sizeof(pd->port_pkeys));

	return 0;
}