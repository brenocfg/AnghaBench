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

/* Variables and functions */
 int /*<<< orphan*/  DCInvalidateRange (void*,int) ; 
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_1 ; 
 scalar_t__ EXI_Deselect (int /*<<< orphan*/ ) ; 
 scalar_t__ EXI_Dma (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EXI_Imm (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_READ ; 
 int /*<<< orphan*/  EXI_SPEED8MHZ ; 
 scalar_t__ EXI_Select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EXI_Sync (int /*<<< orphan*/ ) ; 
 scalar_t__ EXI_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_WRITE ; 

__attribute__((used)) static u32 __read_rom(void *buf,u32 len,u32 offset)
{
	u32 ret;
	u32 loff;

	DCInvalidateRange(buf,len);

	if(EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_1,NULL)==0) return 0;
	if(EXI_Select(EXI_CHANNEL_0,EXI_DEVICE_1,EXI_SPEED8MHZ)==0) {
		EXI_Unlock(EXI_CHANNEL_0);
		return 0;
	}

	ret = 0;
	loff = offset<<6;
	if(EXI_Imm(EXI_CHANNEL_0,&loff,4,EXI_WRITE,NULL)==0) ret |= 0x0001;
	if(EXI_Sync(EXI_CHANNEL_0)==0) ret |= 0x0002;
	if(EXI_Dma(EXI_CHANNEL_0,buf,len,EXI_READ,NULL)==0) ret |= 0x0004;
	if(EXI_Sync(EXI_CHANNEL_0)==0) ret |= 0x0008;
	if(EXI_Deselect(EXI_CHANNEL_0)==0) ret |= 0x0010;
	if(EXI_Unlock(EXI_CHANNEL_0)==0) ret |= 0x00020;

	if(ret) return 0;
	return 1;
}