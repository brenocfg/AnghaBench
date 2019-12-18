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
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_V9 ; 
 int /*<<< orphan*/  assemble_aligned_integer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_integer_with_op (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int default_assemble_integer (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static bool
sparc_assemble_integer (rtx x, unsigned int size, int aligned_p)
{
  /* ??? We only output .xword's for symbols and only then in environments
     where the assembler can handle them.  */
  if (aligned_p && size == 8
      && (GET_CODE (x) != CONST_INT && GET_CODE (x) != CONST_DOUBLE))
    {
      if (TARGET_V9)
	{
	  assemble_integer_with_op ("\t.xword\t", x);
	  return true;
	}
      else
	{
	  assemble_aligned_integer (4, const0_rtx);
	  assemble_aligned_integer (4, x);
	  return true;
	}
    }
  return default_assemble_integer (x, size, aligned_p);
}