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
 int /*<<< orphan*/  inv_debug (char*,int,int,int) ; 
 scalar_t__ jump_out ; 
 int /*<<< orphan*/  ll_add (scalar_t__,int,void*) ; 

void add_link(u32 vaddr,void *src)
{
  u32 page=(vaddr&0xDFFFFFFF)>>12;
  if(page>1024) page=1024+(page&1023);
  inv_debug("add_link: %x -> %x (%d)\n",(int)src,vaddr,page);
  ll_add(jump_out+page,vaddr,src);
  //int ptr=get_pointer(src);
  //inv_debug("add_link: Pointer is to %x\n",(int)ptr);
}