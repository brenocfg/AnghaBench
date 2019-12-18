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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 unsigned int BITS_PER_UNIT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 unsigned int POINTER_SIZE ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_FUNCTION_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_AUTO_PIC ; 
 scalar_t__ TARGET_NO_PIC ; 
 int /*<<< orphan*/  asm_out_file ; 
 int default_assemble_integer (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  fputs (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ia64_assemble_integer (rtx x, unsigned int size, int aligned_p)
{
  if (size == POINTER_SIZE / BITS_PER_UNIT
      && !(TARGET_NO_PIC || TARGET_AUTO_PIC)
      && GET_CODE (x) == SYMBOL_REF
      && SYMBOL_REF_FUNCTION_P (x))
    {
      static const char * const directive[2][2] = {
	  /* 64-bit pointer */  /* 32-bit pointer */
	{ "\tdata8.ua\t@fptr(", "\tdata4.ua\t@fptr("},	/* unaligned */
	{ "\tdata8\t@fptr(",    "\tdata4\t@fptr("}	/* aligned */
      };
      fputs (directive[(aligned_p != 0)][POINTER_SIZE == 32], asm_out_file);
      output_addr_const (asm_out_file, x);
      fputs (")\n", asm_out_file);
      return true;
    }
  return default_assemble_integer (x, size, aligned_p);
}