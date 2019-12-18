#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t s32 ;
struct TYPE_4__ {size_t chan; } ;
struct TYPE_3__ {int chan; } ;

/* Variables and functions */
 TYPE_2__ sicntrl ; 
 TYPE_1__* sipacket ; 

u32 SI_IsChanBusy(s32 chan)
{
	u32 ret = 0;

	if(sipacket[chan].chan!=-1 || sicntrl.chan==chan) ret = 1;

	return ret;
}