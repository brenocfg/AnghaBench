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
typedef  int pointer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

pointer get_clean_addr(pointer addr)
{
  int *ptr=(int *)addr;
  #ifndef HAVE_ARMv7
  ptr+=4;
  #else
  ptr+=6;
  #endif
  if((*ptr&0xFF000000)!=0xeb000000) ptr++;
  assert((*ptr&0xFF000000)==0xeb000000); // bl instruction
  ptr++;
  if((*ptr&0xFF000000)==0xea000000) {
    return (int)ptr+((*ptr<<8)>>6)+8; // follow jump
  }
  return (pointer)ptr;
}