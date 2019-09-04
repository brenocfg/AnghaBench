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
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int sll_ifindex; unsigned short sll_hatype; size_t sll_halen; int /*<<< orphan*/  sll_addr; int /*<<< orphan*/  sll_family; } ;
union sockany {struct sockaddr sa; TYPE_1__ ll; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void copy_lladdr(struct sockaddr **r, union sockany *sa, void *addr, size_t addrlen, int ifindex, unsigned short hatype)
{
	if (addrlen > sizeof(sa->ll.sll_addr)) return;
	sa->ll.sll_family = AF_PACKET;
	sa->ll.sll_ifindex = ifindex;
	sa->ll.sll_hatype = hatype;
	sa->ll.sll_halen = addrlen;
	memcpy(sa->ll.sll_addr, addr, addrlen);
	*r = &sa->sa;
}