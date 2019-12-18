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
#define  DFmode 137 
#define  DImode 136 
#define  HImode 135 
#define  QImode 134 
#define  RFmode 133 
#define  SFmode 132 
#define  SImode 131 
 int TARGET_HPUX ; 
#define  TFmode 130 
#define  TImode 129 
#define  XFmode 128 

__attribute__((used)) static bool
ia64_scalar_mode_supported_p (enum machine_mode mode)
{
  switch (mode)
    {
    case QImode:
    case HImode:
    case SImode:
    case DImode:
    case TImode:
      return true;

    case SFmode:
    case DFmode:
    case XFmode:
    case RFmode:
      return true;

    case TFmode:
      return TARGET_HPUX;

    default:
      return false;
    }
}