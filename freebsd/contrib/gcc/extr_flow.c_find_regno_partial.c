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
typedef  scalar_t__ rtx ;
struct TYPE_2__ {unsigned int regno_to_find; void* retval; } ;
typedef  TYPE_1__ find_regno_partial_param ;

/* Variables and functions */
 int GET_CODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 unsigned int REGNO (void*) ; 
 int /*<<< orphan*/  REG_P (void*) ; 
#define  SIGN_EXTRACT 131 
#define  STRICT_LOW_PART 130 
#define  SUBREG 129 
 void* SUBREG_REG (scalar_t__) ; 
 void* XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
#define  ZERO_EXTRACT 128 

__attribute__((used)) static int
find_regno_partial (rtx *ptr, void *data)
{
  find_regno_partial_param *param = (find_regno_partial_param *)data;
  unsigned reg = param->regno_to_find;
  param->retval = NULL_RTX;

  if (*ptr == NULL_RTX)
    return 0;

  switch (GET_CODE (*ptr))
    {
    case ZERO_EXTRACT:
    case SIGN_EXTRACT:
    case STRICT_LOW_PART:
      if (REG_P (XEXP (*ptr, 0)) && REGNO (XEXP (*ptr, 0)) == reg)
	{
	  param->retval = XEXP (*ptr, 0);
	  return 1;
	}
      break;

    case SUBREG:
      if (REG_P (SUBREG_REG (*ptr))
	  && REGNO (SUBREG_REG (*ptr)) == reg)
	{
	  param->retval = SUBREG_REG (*ptr);
	  return 1;
	}
      break;

    default:
      break;
    }

  return 0;
}