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
#define  CCFPUmode 134 
#define  CCFPmode 133 
#define  CCGCmode 132 
#define  CCGOCmode 131 
#define  CCNOmode 130 
#define  CCZmode 129 
#define  CCmode 128 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ MODE_CC ; 
 int VOIDmode ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static enum machine_mode
ix86_cc_modes_compatible (enum machine_mode m1, enum machine_mode m2)
{
  if (m1 == m2)
    return m1;

  if (GET_MODE_CLASS (m1) != MODE_CC || GET_MODE_CLASS (m2) != MODE_CC)
    return VOIDmode;

  if ((m1 == CCGCmode && m2 == CCGOCmode)
      || (m1 == CCGOCmode && m2 == CCGCmode))
    return CCGCmode;

  switch (m1)
    {
    default:
      gcc_unreachable ();

    case CCmode:
    case CCGCmode:
    case CCGOCmode:
    case CCNOmode:
    case CCZmode:
      switch (m2)
	{
	default:
	  return VOIDmode;

	case CCmode:
	case CCGCmode:
	case CCGOCmode:
	case CCNOmode:
	case CCZmode:
	  return CCmode;
	}

    case CCFPmode:
    case CCFPUmode:
      /* These are only compatible with themselves, which we already
	 checked above.  */
      return VOIDmode;
    }
}