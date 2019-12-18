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
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_CLASS (int) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
#define  MODE_DECIMAL_FLOAT 130 
#define  MODE_FLOAT 129 
#define  MODE_INT 128 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  assemble_real (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

void
s390_output_pool_entry (rtx exp, enum machine_mode mode, unsigned int align)
{
  REAL_VALUE_TYPE r;

  switch (GET_MODE_CLASS (mode))
    {
    case MODE_FLOAT:
    case MODE_DECIMAL_FLOAT:
      gcc_assert (GET_CODE (exp) == CONST_DOUBLE);

      REAL_VALUE_FROM_CONST_DOUBLE (r, exp);
      assemble_real (r, mode, align);
      break;

    case MODE_INT:
      assemble_integer (exp, GET_MODE_SIZE (mode), align, 1);
      break;

    default:
      gcc_unreachable ();
    }
}