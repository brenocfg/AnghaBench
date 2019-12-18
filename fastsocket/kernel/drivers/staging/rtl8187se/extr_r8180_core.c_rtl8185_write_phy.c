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
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 

void rtl8185_write_phy(struct net_device *dev, u8 adr, u32 data)
{
	u32 phyw;

	adr |= 0x80;

	phyw= ((data<<8) | adr);

	// Note that, we must write 0xff7c after 0x7d-0x7f to write BB register.
	write_nic_byte(dev, 0x7f, ((phyw & 0xff000000) >> 24));
	write_nic_byte(dev, 0x7e, ((phyw & 0x00ff0000) >> 16));
	write_nic_byte(dev, 0x7d, ((phyw & 0x0000ff00) >> 8));
	write_nic_byte(dev, 0x7c, ((phyw & 0x000000ff) ));

	/* this is ok to fail when we write AGC table. check for AGC table might be
	 * done by masking with 0x7f instead of 0xff
	 */
	//if(phyr != (data&0xff)) DMESGW("Phy write timeout %x %x %x", phyr, data,adr);
}