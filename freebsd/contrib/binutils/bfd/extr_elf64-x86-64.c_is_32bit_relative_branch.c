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
typedef  int bfd_vma ;
typedef  int bfd_byte ;
typedef  int bfd_boolean ;

/* Variables and functions */

__attribute__((used)) static bfd_boolean
is_32bit_relative_branch (bfd_byte *contents, bfd_vma offset)
{
  /* Opcode		Instruction
     0xe8		call
     0xe9		jump
     0x0f 0x8x		conditional jump */
  return ((offset > 0
	   && (contents [offset - 1] == 0xe8
	       || contents [offset - 1] == 0xe9))
	  || (offset > 1
	      && contents [offset - 2] == 0x0f
	      && (contents [offset - 1] & 0xf0) == 0x80));
}