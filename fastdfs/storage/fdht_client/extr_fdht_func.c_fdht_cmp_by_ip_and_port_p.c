#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int port; int /*<<< orphan*/  ip_addr; } ;
typedef  TYPE_1__ FDHTServerInfo ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdht_cmp_by_ip_and_port_p(const void *p1, const void *p2)
{
	int res;

	res = strcmp(((FDHTServerInfo*)p1)->ip_addr, \
			((FDHTServerInfo*)p2)->ip_addr);
	if (res != 0)
	{
		return res;
	}

	return ((FDHTServerInfo*)p1)->port - \
			((FDHTServerInfo*)p2)->port;
}