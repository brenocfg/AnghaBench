#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u32 ;
typedef  void* s8 ;
struct TYPE_3__ {int button; int triggerL; int triggerR; void* substickY; void* substickX; void* stickY; void* stickX; scalar_t__ analogB; scalar_t__ analogA; } ;
typedef  TYPE_1__ PADStatus ;

/* Variables and functions */
 scalar_t__ _SHIFTR (int,int,int) ; 

__attribute__((used)) static void SPEC0_MakeStatus(u32 chan,u32 *data,PADStatus *status)
{
	status->button = 0;

	if(data[0]&0x00080000) status->button |= 0x0100;
	if(data[0]&0x00200000) status->button |= 0x0200;
	if(data[0]&0x01000000) status->button |= 0x0400;
	if(data[0]&0x00010000) status->button |= 0x0800;
	if(data[0]&0x00100000) status->button |= 0x1000;

	status->stickX = (s8)(data[1]>>16);
	status->stickY = (s8)(data[1]>>24);
	status->substickX = (s8)data[1];
	status->substickY = (s8)(data[1]>>8);
	status->triggerL = (u8)_SHIFTR(data[0],8,8);
	status->triggerR = (u8)(data[0]&0xff);
	status->analogA = 0;
	status->analogB = 0;

	if(status->triggerL>=0xaa) status->button |= 0x40;
	if(status->triggerR>=0xaa) status->button |= 0x20;

	status->stickX -= 128;
	status->stickY -= 128;
	status->substickX -= 128;
	status->substickY -= 128;
}