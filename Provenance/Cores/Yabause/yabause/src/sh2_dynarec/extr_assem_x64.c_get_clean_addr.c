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
typedef  scalar_t__ s32 ;
typedef  scalar_t__ pointer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

pointer get_clean_addr(pointer addr)
{
  u8 *ptr=(u8 *)addr;
  if(ptr[0]==0xB8) {
    assert(ptr[21]==0xE8); // call instruction
    if(ptr[26]==0xE9) return *(s32 *)(ptr+27)+addr+31; // follow jmp
    else return(addr+26);
  }
  /* 64-bit source pointer */
  assert(ptr[26]==0xE8); // call instruction
  if(ptr[31]==0xE9) return *(s32 *)(ptr+32)+addr+36; // follow jmp
  else return(addr+31);
}