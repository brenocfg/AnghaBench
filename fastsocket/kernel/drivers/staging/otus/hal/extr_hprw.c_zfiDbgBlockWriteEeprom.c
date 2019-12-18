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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 int ZM_CMD_WREEPROM ; 
 int /*<<< orphan*/  ZM_EEPROM_WRITE ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32_t zfiDbgBlockWriteEeprom(zdev_t* dev, u32_t addr, u32_t* buf)
{
    u32_t cmd[9];  //2N+1
    u16_t ret,i;

    //cmd[0] = 0x0000B008;
	  /* len[0] : type[0xB0] : seq[?] */

    //cmd[0] = (8*N) | (ZM_CMD_WFLASH << 8);
    cmd[0] = 32 | (ZM_CMD_WREEPROM << 8);    //8N

    for (i=0; i<4; i++)   // i<N
    {
        cmd[(2*i)+1] = addr+(4*i);
        cmd[(2*i)+2] = *(buf+i);
    }

    ret = zfIssueCmd(dev, cmd, 36, ZM_EEPROM_WRITE, 0);    //8N+4

    // added for EEPROMUpdate, wait a moment for prevent cmd queue full!
    //zfwSleep(dev, 1);

    return ret;
}