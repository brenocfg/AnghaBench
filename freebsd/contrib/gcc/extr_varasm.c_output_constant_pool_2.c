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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_DOUBLE ; 
 int /*<<< orphan*/  CONST_VECTOR ; 
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int CONST_VECTOR_NUNITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int GET_MODE_CLASS (int) ; 
 int GET_MODE_INNER (int) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
 unsigned int MIN (unsigned int,int /*<<< orphan*/ ) ; 
#define  MODE_DECIMAL_FLOAT 133 
#define  MODE_FLOAT 132 
#define  MODE_INT 131 
#define  MODE_PARTIAL_INT 130 
#define  MODE_VECTOR_FLOAT 129 
#define  MODE_VECTOR_INT 128 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  assemble_real (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static void
output_constant_pool_2 (enum machine_mode mode, rtx x, unsigned int align)
{
  switch (GET_MODE_CLASS (mode))
    {
    case MODE_FLOAT:
    case MODE_DECIMAL_FLOAT:
      {
	REAL_VALUE_TYPE r;

	gcc_assert (GET_CODE (x) == CONST_DOUBLE);
	REAL_VALUE_FROM_CONST_DOUBLE (r, x);
	assemble_real (r, mode, align);
	break;
      }

    case MODE_INT:
    case MODE_PARTIAL_INT:
      assemble_integer (x, GET_MODE_SIZE (mode), align, 1);
      break;

    case MODE_VECTOR_FLOAT:
    case MODE_VECTOR_INT:
      {
	int i, units;
        enum machine_mode submode = GET_MODE_INNER (mode);
	unsigned int subalign = MIN (align, GET_MODE_BITSIZE (submode));

	gcc_assert (GET_CODE (x) == CONST_VECTOR);
	units = CONST_VECTOR_NUNITS (x);

	for (i = 0; i < units; i++)
	  {
	    rtx elt = CONST_VECTOR_ELT (x, i);
	    output_constant_pool_2 (submode, elt, i ? subalign : align);
	  }
      }
      break;

    default:
      gcc_unreachable ();
    }
}