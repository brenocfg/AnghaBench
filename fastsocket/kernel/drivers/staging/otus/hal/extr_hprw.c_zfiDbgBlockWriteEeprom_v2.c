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
 int ZM_CMD_MEM_WREEPROM ; 
 int /*<<< orphan*/  ZM_EEPROM_WRITE ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32_t zfiDbgBlockWriteEeprom_v2(zdev_t* dev, u32_t addr, u32_t* buf, u32_t wrlen)
{
    u32_t cmd[16];
    u16_t ret,i;

	  /* len[0] : type[0xB0] : seq[?] */
	  /* len = addr(4) + eeprom_block(wrlen) */
    cmd[0] = (wrlen+4) | (ZM_CMD_MEM_WREEPROM << 8);
    cmd[1] = addr;

    for (i=0; i<(wrlen/4); i++)   // i<wrlen/4
    {
        cmd[2+i] = *(buf+i);
    }
    /* cmd_info(4) + addr(4) + eeprom(wrlen) */
    ret = zfIssueCmd(dev, cmd, (u16_t)(wrlen+8), ZM_EEPROM_WRITE, 0);

    return ret;
}