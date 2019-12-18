#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int* fp_load; int* fp_store; int* sse_load; int* sse_store; int* mmx_load; int* mmx_store; int* int_load; int movzbl_load; int* int_store; } ;

/* Variables and functions */
#define  DFmode 130 
 scalar_t__ FLOAT_CLASS_P (int) ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ MMX_CLASS_P (int) ; 
 int /*<<< orphan*/  Q_CLASS_P (int) ; 
#define  SFmode 129 
 scalar_t__ SSE_CLASS_P (int) ; 
 int TFmode ; 
 int UNITS_PER_WORD ; 
#define  XFmode 128 
 TYPE_1__* ix86_cost ; 

int
ix86_memory_move_cost (enum machine_mode mode, enum reg_class class, int in)
{
  if (FLOAT_CLASS_P (class))
    {
      int index;
      switch (mode)
	{
	  case SFmode:
	    index = 0;
	    break;
	  case DFmode:
	    index = 1;
	    break;
	  case XFmode:
	    index = 2;
	    break;
	  default:
	    return 100;
	}
      return in ? ix86_cost->fp_load [index] : ix86_cost->fp_store [index];
    }
  if (SSE_CLASS_P (class))
    {
      int index;
      switch (GET_MODE_SIZE (mode))
	{
	  case 4:
	    index = 0;
	    break;
	  case 8:
	    index = 1;
	    break;
	  case 16:
	    index = 2;
	    break;
	  default:
	    return 100;
	}
      return in ? ix86_cost->sse_load [index] : ix86_cost->sse_store [index];
    }
  if (MMX_CLASS_P (class))
    {
      int index;
      switch (GET_MODE_SIZE (mode))
	{
	  case 4:
	    index = 0;
	    break;
	  case 8:
	    index = 1;
	    break;
	  default:
	    return 100;
	}
      return in ? ix86_cost->mmx_load [index] : ix86_cost->mmx_store [index];
    }
  switch (GET_MODE_SIZE (mode))
    {
      case 1:
	if (in)
	  return (Q_CLASS_P (class) ? ix86_cost->int_load[0]
		  : ix86_cost->movzbl_load);
	else
	  return (Q_CLASS_P (class) ? ix86_cost->int_store[0]
		  : ix86_cost->int_store[0] + 4);
	break;
      case 2:
	return in ? ix86_cost->int_load[1] : ix86_cost->int_store[1];
      default:
	/* Compute number of 32bit moves needed.  TFmode is moved as XFmode.  */
	if (mode == TFmode)
	  mode = XFmode;
	return ((in ? ix86_cost->int_load[2] : ix86_cost->int_store[2])
		* (((int) GET_MODE_SIZE (mode)
		    + UNITS_PER_WORD - 1) / UNITS_PER_WORD));
    }
}