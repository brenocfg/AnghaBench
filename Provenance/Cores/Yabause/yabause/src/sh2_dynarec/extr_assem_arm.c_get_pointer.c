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

pointer get_pointer(void *stub)
{
  //printf("get_pointer(%x)\n",(int)stub);
  int *ptr=(int *)(stub+4);
  assert((*ptr&0x0ff00000)==0x05900000);
  u32 offset=*ptr&0xfff;
  int **l_ptr=(void *)ptr+offset+8;
  int *i_ptr=*l_ptr;
  assert((*i_ptr&0x0f000000)==0x0a000000);
  return (pointer)i_ptr+((*i_ptr<<8)>>6)+8;
}