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
typedef  size_t s32 ;

/* Variables and functions */
 scalar_t__ BYTE_ADDRESSING ; 
 scalar_t__ SECTOR_ADDRESSING ; 
 scalar_t__* _ioAddressingType ; 

__attribute__((used)) static void __convert_sector(s32 drv_no,u32 sector_no,u8 *arg)
{
	if(_ioAddressingType[drv_no]==BYTE_ADDRESSING) {
		arg[0] = (sector_no>>15)&0xff;
		arg[1] = (sector_no>>7)&0xff;
		arg[2] = (sector_no<<1)&0xff;
		arg[3] = (sector_no<<9)&0xff;
	} else if(_ioAddressingType[drv_no]==SECTOR_ADDRESSING) {
		arg[0] = (sector_no>>24)&0xff;
		arg[1] = (sector_no>>16)&0xff;
		arg[2] = (sector_no>>8)&0xff;
		arg[3] = sector_no&0xff;
	}
}