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
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_CTRL ; 
 int EFUSE_MAC_LEN ; 
 int read_nic_byte (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 

extern	u8
EFUSE_Read1Byte(struct net_device* dev, u16	Address)
{
	u8	data;
	u8	Bytetemp = {0x00};
	u8	temp = {0x00};
	u32	k=0;

	if (Address < EFUSE_MAC_LEN)	//E-fuse 512Byte
	{
		//Write E-fuse Register address bit0~7
		temp = Address & 0xFF;
		write_nic_byte(dev, EFUSE_CTRL+1, temp);
		Bytetemp = read_nic_byte(dev, EFUSE_CTRL+2);
		//Write E-fuse Register address bit8~9
		temp = ((Address >> 8) & 0x03) | (Bytetemp & 0xFC);
		write_nic_byte(dev, EFUSE_CTRL+2, temp);

		//Write 0x30[31]=0
		Bytetemp = read_nic_byte(dev, EFUSE_CTRL+3);
		temp = Bytetemp & 0x7F;
		write_nic_byte(dev, EFUSE_CTRL+3, temp);

		//Wait Write-ready (0x30[31]=1)
		Bytetemp = read_nic_byte(dev, EFUSE_CTRL+3);
		while(!(Bytetemp & 0x80))
		{
			Bytetemp = read_nic_byte(dev, EFUSE_CTRL+3);
			k++;
			if(k==1000)
			{
				k=0;
				break;
			}
		}
		data=read_nic_byte(dev, EFUSE_CTRL);
		return data;
	}
	else
		return 0xFF;

}