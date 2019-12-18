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
struct b43_wldev {TYPE_1__* dfsentry; } ;
struct TYPE_2__ {unsigned int shm16read_routing_next; unsigned int shm16read_addr_next; } ;

/* Variables and functions */
 unsigned int B43_MAX_SHM_ADDR ; 
 unsigned int B43_MAX_SHM_ROUTING ; 
 unsigned int B43_SHM_SHARED ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int shm16read__write_file(struct b43_wldev *dev,
				 const char *buf, size_t count)
{
	unsigned int routing, addr;
	int res;

	res = sscanf(buf, "0x%X 0x%X", &routing, &addr);
	if (res != 2)
		return -EINVAL;
	if (routing > B43_MAX_SHM_ROUTING)
		return -EADDRNOTAVAIL;
	if (addr > B43_MAX_SHM_ADDR)
		return -EADDRNOTAVAIL;
	if (routing == B43_SHM_SHARED) {
		if ((addr % 2) != 0)
			return -EADDRNOTAVAIL;
	}

	dev->dfsentry->shm16read_routing_next = routing;
	dev->dfsentry->shm16read_addr_next = addr;

	return 0;
}