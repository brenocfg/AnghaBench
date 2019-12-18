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
#define  CCSRmode 134 
#define  CCSmode 133 
#define  CCTmode 132 
#define  CCURmode 131 
#define  CCUmode 130 
#define  CCZ1mode 129 
#define  CCZmode 128 
 int VOIDmode ; 

__attribute__((used)) static enum machine_mode
s390_cc_modes_compatible (enum machine_mode m1, enum machine_mode m2)
{
  if (m1 == m2)
    return m1;

  switch (m1)
    {
    case CCZmode:
      if (m2 == CCUmode || m2 == CCTmode || m2 == CCZ1mode
	  || m2 == CCSmode || m2 == CCSRmode || m2 == CCURmode)
        return m2;
      return VOIDmode;

    case CCSmode:
    case CCUmode:
    case CCTmode:
    case CCSRmode:
    case CCURmode:
    case CCZ1mode:
      if (m2 == CCZmode)
	return m1;
      
      return VOIDmode;

    default:
      return VOIDmode;
    }
  return VOIDmode;
}