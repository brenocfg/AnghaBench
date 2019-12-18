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
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD ; 
 int /*<<< orphan*/  do_93c46 (struct net_device*,int) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

u16 Read93C46(struct net_device*	dev,	u16	Reg	)
{

   	u8  	clear[1] = {0x0};      // cs=0 , sk=0 , di=0 , do=0
	u8  	cs[1] = {0x88};        // cs=1 , sk=0 , di=0 , do=0
	u8  	cssk[1] = {0x8c};      // cs=1 , sk=1 , di=0 , do=0
	u8  	csdi[1] = {0x8a};      // cs=1 , sk=0 , di=1 , do=0
   	u8  	csskdi[1] = {0x8e};    // cs=1 , sk=1 , di=1 , do=0
	//u8  	di[1] = {0x82};        // cs=0 , sk=0 , di=1 , do=0
	u8  	EepromSEL[1]={0x00};
	u8  	address;

	u16   	storedataF[1] = {0x0};   //93c46 data packet for 16bits
	u8   	t,data[1],storedata[1];


	address = (u8)Reg;

	// Suggested by SD1 Alex, 2008.10.20. Revised by Roger.
	*EepromSEL= read_nic_byte(dev, EPROM_CMD);

	if((*EepromSEL & 0x10) == 0x10) // select 93c46
	{
		address = address | 0x80;

		write_nic_byte(dev, EPROM_CMD, csdi[0]);
		write_nic_byte(dev, EPROM_CMD, csskdi[0]);
   		do_93c46(dev, address);
	}


	for(t=0 ; t<16 ; t++)      //if read 93c46 , t=16
	{
		write_nic_byte(dev, EPROM_CMD, cs[0]);
		write_nic_byte(dev, EPROM_CMD, cssk[0]);
		*data= read_nic_byte(dev, EPROM_CMD);

		if(*data & 0x8d) //original code
		{
			*data = *data & 0x01;
			*storedata = *data;
		}
		else
		{
			*data = *data & 0x01 ;
			*storedata = *data;
		}
		*storedataF = (*storedataF << 1 ) + *storedata;
	}
	write_nic_byte(dev, EPROM_CMD, cs[0]);
	write_nic_byte(dev, EPROM_CMD, clear[0]);

	return *storedataF;
}