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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int BLKmode ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int GET_MODE_CLASS (int) ; 
#define  MODE_CC 137 
#define  MODE_COMPLEX_FLOAT 136 
#define  MODE_COMPLEX_INT 135 
#define  MODE_DECIMAL_FLOAT 134 
#define  MODE_FLOAT 133 
#define  MODE_INT 132 
#define  MODE_PARTIAL_INT 131 
#define  MODE_RANDOM 130 
#define  MODE_VECTOR_FLOAT 129 
#define  MODE_VECTOR_INT 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int mode_for_size (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

enum machine_mode
int_mode_for_mode (enum machine_mode mode)
{
  switch (GET_MODE_CLASS (mode))
    {
    case MODE_INT:
    case MODE_PARTIAL_INT:
      break;

    case MODE_COMPLEX_INT:
    case MODE_COMPLEX_FLOAT:
    case MODE_FLOAT:
    case MODE_DECIMAL_FLOAT:
    case MODE_VECTOR_INT:
    case MODE_VECTOR_FLOAT:
      mode = mode_for_size (GET_MODE_BITSIZE (mode), MODE_INT, 0);
      break;

    case MODE_RANDOM:
      if (mode == BLKmode)
	break;

      /* ... fall through ...  */

    case MODE_CC:
    default:
      gcc_unreachable ();
    }

  return mode;
}