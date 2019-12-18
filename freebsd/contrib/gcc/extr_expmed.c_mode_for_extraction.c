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
struct insn_data {TYPE_1__* operand; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum extraction_pattern { ____Placeholder_extraction_pattern } extraction_pattern ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 size_t CODE_FOR_extv ; 
 size_t CODE_FOR_extzv ; 
 size_t CODE_FOR_insv ; 
#define  EP_extv 130 
#define  EP_extzv 129 
#define  EP_insv 128 
 int /*<<< orphan*/  HAVE_extv ; 
 int /*<<< orphan*/  HAVE_extzv ; 
 int /*<<< orphan*/  HAVE_insv ; 
 int MAX_MACHINE_MODE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 struct insn_data* insn_data ; 
 int word_mode ; 

enum machine_mode
mode_for_extraction (enum extraction_pattern pattern, int opno)
{
  const struct insn_data *data;

  switch (pattern)
    {
    case EP_insv:
      if (HAVE_insv)
	{
	  data = &insn_data[CODE_FOR_insv];
	  break;
	}
      return MAX_MACHINE_MODE;

    case EP_extv:
      if (HAVE_extv)
	{
	  data = &insn_data[CODE_FOR_extv];
	  break;
	}
      return MAX_MACHINE_MODE;

    case EP_extzv:
      if (HAVE_extzv)
	{
	  data = &insn_data[CODE_FOR_extzv];
	  break;
	}
      return MAX_MACHINE_MODE;

    default:
      gcc_unreachable ();
    }

  if (opno == -1)
    return VOIDmode;

  /* Everyone who uses this function used to follow it with
     if (result == VOIDmode) result = word_mode; */
  if (data->operand[opno].mode == VOIDmode)
    return word_mode;
  return data->operand[opno].mode;
}