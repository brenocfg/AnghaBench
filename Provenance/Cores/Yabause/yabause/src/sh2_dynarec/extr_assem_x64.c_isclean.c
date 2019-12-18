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
typedef  scalar_t__ pointer ;

/* Variables and functions */

int isclean(pointer addr)
{
  u8 *ptr=(u8 *)addr;
  if(ptr[0]==0xB8) {
    if(ptr[0]!=0xB8) return 1; // mov imm,%eax
    if(ptr[5]!=0xBB) return 1; // mov imm,%ebx
    if(ptr[10]!=0xB9) return 1; // mov imm,%ecx
    if(ptr[15]!=0x41) return 1; // rex prefix
    if(ptr[16]!=0xBC) return 1; // mov imm,%r12d
    if(ptr[21]!=0xE8) return 1; // call instruction
  }else{
    if(ptr[0]!=0x48) return 1; // rex prefix
    if(ptr[1]!=0xB8) return 1; // mov imm,%rax
    if(ptr[10]!=0xBB) return 1; // mov imm,%ebx
    if(ptr[15]!=0xB9) return 1; // mov imm,%ecx
    if(ptr[20]!=0x41) return 1; // rex prefix
    if(ptr[21]!=0xBC) return 1; // mov imm,%r12d
    if(ptr[26]!=0xE8) return 1; // call instruction
  }
  return 0;
}