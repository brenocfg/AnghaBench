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
 int /*<<< orphan*/  assert (int) ; 

void get_bounds(pointer addr,u32 *start,u32 *end)
{
  u32 *ptr=(u32 *)addr;
  #ifndef HAVE_ARMv7
  // get from literal pool
  assert((*ptr&0xFFF00000)==0xe5900000);
  u32 offset=*ptr&0xfff;
  u32 *l_ptr=(void *)ptr+offset+8;
  u32 source=l_ptr[0];
  //u32 copy=l_ptr[1];
  u32 len=l_ptr[2];
  ptr+=4;
  #else
  // ARMv7 movw/movt
  assert((*ptr&0xFFF00000)==0xe3000000);
  u32 source=(ptr[0]&0xFFF)+((ptr[0]>>4)&0xF000)+((ptr[2]<<16)&0xFFF0000)+((ptr[2]<<12)&0xF0000000);
  //u32 copy=(ptr[1]&0xFFF)+((ptr[1]>>4)&0xF000)+((ptr[3]<<16)&0xFFF0000)+((ptr[3]<<12)&0xF0000000);
  u32 len=(ptr[4]&0xFFF)+((ptr[4]>>4)&0xF000);
  ptr+=6;
  #endif
  if((*ptr&0xFF000000)!=0xeb000000) ptr++;
  assert((*ptr&0xFF000000)==0xeb000000); // bl instruction
  *start=source;
  *end=source+len;
}