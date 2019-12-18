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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  WPADDataCallback ;

/* Variables and functions */
 scalar_t__ WPAD_CHAN_0 ; 
 scalar_t__ WPAD_ERR_NONE ; 
 scalar_t__ WPAD_MAX_WIIMOTES ; 
 scalar_t__ pad_readpending_temp (scalar_t__) ; 

s32 WPAD_ReadPending(s32 chan, WPADDataCallback datacb)
{
   u32 i;
   s32 count = 0;
   s32 ret;

   for(i= WPAD_CHAN_0; i < WPAD_MAX_WIIMOTES; i++)
      if((ret = pad_readpending_temp(i)) >= WPAD_ERR_NONE)
         count += ret;
   return count;
}