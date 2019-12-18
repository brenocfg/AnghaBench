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
#define  CONST_DOUBLE 130 
#define  CONST_INT 129 
#define  CONST_VECTOR 128 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legitimate_constant_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ix86_cannot_force_const_mem (rtx x)
{
  /* We can always put integral constants and vectors in memory.  */
  switch (GET_CODE (x))
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
      return false;

    default:
      break;
    }
  return !legitimate_constant_p (x);
}