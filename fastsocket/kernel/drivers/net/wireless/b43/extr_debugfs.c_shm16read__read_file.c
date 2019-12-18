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
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {TYPE_1__* dfsentry; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {unsigned int shm16read_routing_next; unsigned int shm16read_addr_next; } ;

/* Variables and functions */
 unsigned int B43_MAX_SHM_ADDR ; 
 unsigned int B43_MAX_SHM_ROUTING ; 
 int /*<<< orphan*/  EDESTADDRREQ ; 
 int /*<<< orphan*/  b43_shm_read16 (struct b43_wldev*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fappend (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t shm16read__read_file(struct b43_wldev *dev,
				    char *buf, size_t bufsize)
{
	ssize_t count = 0;
	unsigned int routing, addr;
	u16 val;

	routing = dev->dfsentry->shm16read_routing_next;
	addr = dev->dfsentry->shm16read_addr_next;
	if ((routing > B43_MAX_SHM_ROUTING) ||
	    (addr > B43_MAX_SHM_ADDR))
		return -EDESTADDRREQ;

	val = b43_shm_read16(dev, routing, addr);
	fappend("0x%04X\n", val);

	return count;
}