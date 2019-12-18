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
 int /*<<< orphan*/  DMESGW (char*,int,int) ; 
 int MAX_PHY ; 
 int /*<<< orphan*/  PHY_ADR ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

void write_phy(struct net_device *dev, u8 adr, u8 data)
{
	u32 phy;
	int i;

	phy = 0xff0000;
	phy |= adr;
	phy |= 0x80; /* this should enable writing */
	phy |= (data<<8);

	//PHY_ADR, PHY_R and PHY_W  are contig and treated as one dword
	write_nic_dword(dev,PHY_ADR, phy);

	phy= 0xffff00;
	phy |= adr;

	write_nic_dword(dev,PHY_ADR, phy);
	for(i=0;i<MAX_PHY;i++){
		phy=read_nic_dword(dev,PHY_ADR);
		phy= phy & 0xff0000;
		phy= phy >> 16;
		if(phy == data){ //SUCCESS!
			force_pci_posting(dev);
			mdelay(3); //random value
			return;
		}else{
			force_pci_posting(dev);
			mdelay(3); //random value
		}
	}
	DMESGW ("Phy writing %x %x failed!", adr,data);
}