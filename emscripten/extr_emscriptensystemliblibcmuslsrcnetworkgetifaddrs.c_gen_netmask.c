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
typedef  union sockany {int dummy; } sockany ;
typedef  int uint8_t ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  copy_addr (struct sockaddr**,int,union sockany*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void gen_netmask(struct sockaddr **r, int af, union sockany *sa, int prefixlen)
{
	uint8_t addr[16] = {0};
	int i;

	if (prefixlen > 8*sizeof(addr)) prefixlen = 8*sizeof(addr);
	i = prefixlen / 8;
	memset(addr, 0xff, i);
	if (i < sizeof(addr)) addr[i++] = 0xff << (8 - (prefixlen % 8));
	copy_addr(r, af, sa, addr, sizeof(addr), 0);
}