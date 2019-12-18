#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int s32 ;
struct TYPE_2__ {int offset; scalar_t__ sync; scalar_t__ srambuf; } ;

/* Variables and functions */
 scalar_t__ __sram_write (scalar_t__,int,int) ; 
 TYPE_1__ sramcntrl ; 

__attribute__((used)) static s32 __sram_writecallback(s32 chn,s32 dev)
{
	sramcntrl.sync = __sram_write(sramcntrl.srambuf+sramcntrl.offset,sramcntrl.offset,(64-sramcntrl.offset));
	if(sramcntrl.sync) sramcntrl.offset = 64;

	return 1;
}