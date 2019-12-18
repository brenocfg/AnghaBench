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
 int /*<<< orphan*/  BITS_PER_UNIT ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 char* HOST_WIDE_INT_PRINT_HEX ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_integer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 char* integer_asm_op (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dw2_assemble_integer (int size, rtx x)
{
  const char *op = integer_asm_op (size, FALSE);

  if (op)
    {
      fputs (op, asm_out_file);
      if (GET_CODE (x) == CONST_INT)
	fprintf (asm_out_file, HOST_WIDE_INT_PRINT_HEX, INTVAL (x));
      else
	output_addr_const (asm_out_file, x);
    }
  else
    assemble_integer (x, size, BITS_PER_UNIT, 1);
}