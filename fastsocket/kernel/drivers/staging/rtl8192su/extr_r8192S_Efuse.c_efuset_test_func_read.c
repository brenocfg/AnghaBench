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
typedef  int /*<<< orphan*/  txpowertable ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  ocr ;
typedef  int /*<<< orphan*/  macaddr ;
typedef  int /*<<< orphan*/  chipid ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_CCCR ; 
 int /*<<< orphan*/  EFUSE_CHIP_ID ; 
 int /*<<< orphan*/  EFUSE_MAC_ADDR ; 
 int /*<<< orphan*/  EFUSE_TXPW_TAB ; 
 int /*<<< orphan*/  efuse_read_data (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void efuset_test_func_read(struct net_device* dev)
{
	u8 chipid[2];
	u8 ocr[3];
	u8 macaddr[6];
	u8 txpowertable[28];

	memset(chipid,0,sizeof(u8)*2);
	efuse_read_data(dev,EFUSE_CHIP_ID,chipid,sizeof(chipid));

	memset(ocr,0,sizeof(u8)*3);
	efuse_read_data(dev,EFUSE_CCCR,ocr,sizeof(ocr));

	memset(macaddr,0,sizeof(u8)*6);
	efuse_read_data(dev,EFUSE_MAC_ADDR,macaddr,sizeof(macaddr));

	memset(txpowertable,0,sizeof(u8)*28);
	efuse_read_data(dev,EFUSE_TXPW_TAB,txpowertable,sizeof(txpowertable));
}