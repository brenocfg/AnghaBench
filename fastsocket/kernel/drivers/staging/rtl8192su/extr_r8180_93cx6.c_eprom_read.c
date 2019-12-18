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
typedef  int u32 ;
struct r8192_priv {scalar_t__ epromtype; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EPROM_93c56 ; 
 int /*<<< orphan*/  EPROM_CMD ; 
 int EPROM_CMD_NORMAL ; 
 int EPROM_CMD_OPERATING_MODE_SHIFT ; 
 int EPROM_CMD_PROGRAM ; 
 int /*<<< orphan*/  EPROM_DELAY ; 
 int /*<<< orphan*/  eprom_ck_cycle (struct net_device*) ; 
 int /*<<< orphan*/  eprom_cs (struct net_device*,int) ; 
 int eprom_r (struct net_device*) ; 
 int /*<<< orphan*/  eprom_send_bits_string (struct net_device*,short*,int) ; 
 int /*<<< orphan*/  eprom_w (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte_E (struct net_device*,int /*<<< orphan*/ ,int) ; 

u32 eprom_read(struct net_device *dev, u32 addr)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	short read_cmd[]={1,1,0};
	short addr_str[8];
	int i;
	int addr_len;
	u32 ret;

	ret=0;
        //enable EPROM programming
	write_nic_byte_E(dev, EPROM_CMD,
		       (EPROM_CMD_PROGRAM<<EPROM_CMD_OPERATING_MODE_SHIFT));
	force_pci_posting(dev);
	udelay(EPROM_DELAY);

	if (priv->epromtype==EPROM_93c56){
		addr_str[7]=addr & 1;
		addr_str[6]=addr & (1<<1);
		addr_str[5]=addr & (1<<2);
		addr_str[4]=addr & (1<<3);
		addr_str[3]=addr & (1<<4);
		addr_str[2]=addr & (1<<5);
		addr_str[1]=addr & (1<<6);
		addr_str[0]=addr & (1<<7);
		addr_len=8;
	}else{
		addr_str[5]=addr & 1;
		addr_str[4]=addr & (1<<1);
		addr_str[3]=addr & (1<<2);
		addr_str[2]=addr & (1<<3);
		addr_str[1]=addr & (1<<4);
		addr_str[0]=addr & (1<<5);
		addr_len=6;
	}
	eprom_cs(dev, 1);
	eprom_ck_cycle(dev);
	eprom_send_bits_string(dev, read_cmd, 3);
	eprom_send_bits_string(dev, addr_str, addr_len);

	//keep chip pin D to low state while reading.
	//I'm unsure if it is necessary, but anyway shouldn't hurt
	eprom_w(dev, 0);

	for(i=0;i<16;i++){
		//eeprom needs a clk cycle between writing opcode&adr
		//and reading data. (eeprom outs a dummy 0)
		eprom_ck_cycle(dev);
		ret |= (eprom_r(dev)<<(15-i));
	}

	eprom_cs(dev, 0);
	eprom_ck_cycle(dev);

	//disable EPROM programming
	write_nic_byte_E(dev, EPROM_CMD,
		       (EPROM_CMD_NORMAL<<EPROM_CMD_OPERATING_MODE_SHIFT));
	return ret;
}