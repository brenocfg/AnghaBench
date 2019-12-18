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
typedef  size_t s32 ;

/* Variables and functions */
 size_t WPAD_ERR_NONE ; 
 size_t WPAD_ERR_QUEUE_EMPTY ; 
 size_t WPAD_ReadEvent (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpaddata ; 

__attribute__((used)) static s32 pad_readpending_temp(s32 chan)
{
   s32 count = 0;
   s32 ret;

   while(1)
   {
      ret = WPAD_ReadEvent(chan, &wpaddata[chan]);
      if(ret < WPAD_ERR_NONE)
         break;
      count++;
   }
   if(ret == WPAD_ERR_QUEUE_EMPTY) return count;
   return ret;
}