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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ pointer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void set_jump_target(pointer addr,pointer target)
{
  u8 *ptr=(u8 *)addr;
  if(*ptr==0x0f)
  {
    assert(ptr[1]>=0x80&&ptr[1]<=0x8f);
    u32 *ptr2=(u32 *)(ptr+2);
    *ptr2=target-(u32)ptr2-4;
  }
  else if(*ptr==0xe8||*ptr==0xe9) {
    u32 *ptr2=(u32 *)(ptr+1);
    *ptr2=target-(u32)ptr2-4;
  }
  else
  {
    assert(*ptr==0xc7); /* mov immediate (store address) */
    u32 *ptr2=(u32 *)(ptr+6);
    *ptr2=target;
  }
}