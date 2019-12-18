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
typedef  int /*<<< orphan*/  u32 ;
struct igb_adapter {int dummy; } ;

/* Variables and functions */
 int igb_set_vf_mac (struct igb_adapter*,int,unsigned char*) ; 
 scalar_t__ is_valid_ether_addr (unsigned char*) ; 

__attribute__((used)) static int igb_set_vf_mac_addr(struct igb_adapter *adapter, u32 *msg, int vf)
{
	/* The VF MAC Address is stored in a packed array of bytes
	 * starting at the second 32 bit word of the msg array
	 */
	unsigned char *addr = (char *)&msg[1];
	int err = -1;

	if (is_valid_ether_addr(addr))
		err = igb_set_vf_mac(adapter, vf, addr);

	return err;
}