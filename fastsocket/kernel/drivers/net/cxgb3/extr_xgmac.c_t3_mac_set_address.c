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
typedef  int /*<<< orphan*/  u8 ;
struct cmac {unsigned int nucast; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  set_addr_filter (struct cmac*,unsigned int,int /*<<< orphan*/ *) ; 

int t3_mac_set_address(struct cmac *mac, unsigned int idx, u8 addr[6])
{
	if (idx >= mac->nucast)
		return -EINVAL;
	set_addr_filter(mac, idx, addr);
	return 0;
}