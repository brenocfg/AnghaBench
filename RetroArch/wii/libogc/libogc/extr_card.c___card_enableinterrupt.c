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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BUSY ; 
 scalar_t__ CARD_ERROR_NOCARD ; 
 scalar_t__ CARD_ERROR_READY ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 scalar_t__ EXI_Deselect (scalar_t__) ; 
 scalar_t__ EXI_Imm (scalar_t__,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_SPEED16MHZ ; 
 scalar_t__ EXI_Select (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EXI_Sync (scalar_t__) ; 
 int /*<<< orphan*/  EXI_WRITE ; 

__attribute__((used)) static s32 __card_enableinterrupt(s32 chn,u32 enable)
{
	u8 val[2];
	u32 err;
	s32 ret;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if(EXI_Select(chn,EXI_DEVICE_0,EXI_SPEED16MHZ)==0) return CARD_ERROR_NOCARD;

	err = 0;
	val[0] = 0x81;
	if(enable) val[1] = 0x01;
	else val[1] = 0x00;
	if(EXI_Imm(chn,val,2,EXI_WRITE,NULL)==0) err |= 0x01;
	if(EXI_Sync(chn)==0) err |= 0x02;
	if(EXI_Deselect(chn)==0) err |= 0x04;

	if(err) ret = CARD_ERROR_BUSY;
	else ret = CARD_ERROR_READY;

	return ret;
}