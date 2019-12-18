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
typedef  scalar_t__ pointer ;

/* Variables and functions */
 scalar_t__ verify_code ; 

int isclean(pointer addr)
{
  #ifndef HAVE_ARMv7
  int *ptr=((u32 *)addr)+4;
  #else
  int *ptr=((u32 *)addr)+6;
  #endif
  if((*ptr&0xFF000000)!=0xeb000000) ptr++;
  if((*ptr&0xFF000000)!=0xeb000000) return 1; // bl instruction
  if((int)ptr+((*ptr<<8)>>6)+8==(int)verify_code) return 0;
  return 1;
}