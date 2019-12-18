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
 size_t currentpos ; 
 int mbufferSizeInBytes ; 
 int* soundoffset ; 

__attribute__((used)) static u32 SNDOpenSLGetAudioSpace(void)
{
   
   // printf("SNDOpenSLGetAudioSpace %d,%d",soundoffset,mbufferSizeInBytes);
   
   int val = (mbufferSizeInBytes-soundoffset[currentpos]);
   if( val < 0 ) return 0;
   return val;
}