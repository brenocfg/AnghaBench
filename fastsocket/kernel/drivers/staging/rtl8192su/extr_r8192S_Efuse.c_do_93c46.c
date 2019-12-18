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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void do_93c46(struct net_device* dev,  u8 addorvalue)
{
    	//u8  clear[1] = {0x0};      // cs=0 , sk=0 , di=0 , do=0
	u8  cs[1] = {0x88};        // cs=1 , sk=0 , di=0 , do=0
	u8  cssk[1] = {0x8c};      // cs=1 , sk=1 , di=0 , do=0
	u8  csdi[1] = {0x8a};      // cs=1 , sk=0 , di=1 , do=0
    	u8  csskdi[1] = {0x8e};    // cs=1 , sk=1 , di=1 , do=0
	//u8  di[1] = {0x82};        // cs=0 , sk=0 , di=1 , do=0
    	u8  count;

    	for(count=0 ; count<8 ; count++)
	{
		if((addorvalue&0x80)!=0)
		{
			write_nic_byte(dev, EPROM_CMD, csdi[0]);
			write_nic_byte(dev, EPROM_CMD, csskdi[0]);
		}
		else
		{
			write_nic_byte(dev, EPROM_CMD, cs[0]);
			write_nic_byte(dev, EPROM_CMD, cssk[0]);
		}
		addorvalue = addorvalue << 1;
	}
}