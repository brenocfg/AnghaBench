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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tmpdata ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  macaddr ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_CCCR ; 
 int /*<<< orphan*/  EFUSE_MAC_ADDR ; 
 int /*<<< orphan*/  EFUSE_SDIO_SETTING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  efuse_write_data (struct net_device*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

void efuset_test_func_write(struct net_device* dev)
{
	u32 bWordUnit = TRUE;
	u8 CCCR=0x02,SDIO_SETTING = 0xFF;
	u8 tmpdata[2];

	u8 macaddr[6] = {0x00,0xe0,0x4c,0x87,0x12,0x66};
	efuse_write_data(dev,EFUSE_MAC_ADDR,macaddr,sizeof(macaddr),bWordUnit);

	bWordUnit = FALSE;
	efuse_write_data(dev,EFUSE_CCCR,&CCCR,sizeof(u8),bWordUnit);

	bWordUnit = FALSE;
	efuse_write_data(dev,EFUSE_SDIO_SETTING,&SDIO_SETTING,sizeof(u8),bWordUnit);

	bWordUnit = TRUE;
	tmpdata[0] =SDIO_SETTING ;
	tmpdata[1] =CCCR ;
	efuse_write_data(dev,EFUSE_SDIO_SETTING,tmpdata,sizeof(tmpdata),bWordUnit);

}