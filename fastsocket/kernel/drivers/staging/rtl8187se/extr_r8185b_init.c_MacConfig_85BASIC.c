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
 int BIT2 ; 
 int IntMig ; 
 int /*<<< orphan*/  MacConfig_85BASIC_HardCode (struct net_device*) ; 
 int PHYPR ; 
 int /*<<< orphan*/  PlatformIOWrite1Byte (struct net_device*,int,int) ; 
 int /*<<< orphan*/  PlatformIOWrite4Byte (struct net_device*,int,int) ; 
 int TID_AC_MAP ; 
 int read_nic_byte (struct net_device*,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int,int) ; 

__attribute__((used)) static void
MacConfig_85BASIC(
	struct net_device *dev)
{

       u8			u1DA;
	MacConfig_85BASIC_HardCode(dev);

	//============================================================================

	// Follow TID_AC_MAP of WMac.
	write_nic_word(dev, TID_AC_MAP, 0xfa50);

	// Interrupt Migration, Jong suggested we use set 0x0000 first, 2005.12.14, by rcnjko.
	write_nic_word(dev, IntMig, 0x0000);

	// Prevent TPC to cause CRC error. Added by Annie, 2006-06-10.
	PlatformIOWrite4Byte(dev, 0x1F0, 0x00000000);
	PlatformIOWrite4Byte(dev, 0x1F4, 0x00000000);
	PlatformIOWrite1Byte(dev, 0x1F8, 0x00);

	// Asked for by SD3 CM Lin, 2006.06.27, by rcnjko.
	//PlatformIOWrite4Byte(dev, RFTiming, 0x00004001);
//by amy
	// power save parameter based on "87SE power save parameters 20071127.doc", as follow.

	//Enable DA10 TX power saving
	u1DA = read_nic_byte(dev, PHYPR);
	write_nic_byte(dev, PHYPR, (u1DA | BIT2) );

	//POWER:
	write_nic_word(dev, 0x360, 0x1000);
	write_nic_word(dev, 0x362, 0x1000);

	// AFE.
	write_nic_word(dev, 0x370, 0x0560);
	write_nic_word(dev, 0x372, 0x0560);
	write_nic_word(dev, 0x374, 0x0DA4);
	write_nic_word(dev, 0x376, 0x0DA4);
	write_nic_word(dev, 0x378, 0x0560);
	write_nic_word(dev, 0x37A, 0x0560);
	write_nic_word(dev, 0x37C, 0x00EC);
//	write_nic_word(dev, 0x37E, 0x00FE);//-edward
	write_nic_word(dev, 0x37E, 0x00EC);//+edward
       write_nic_byte(dev, 0x24E,0x01);
//by amy

}