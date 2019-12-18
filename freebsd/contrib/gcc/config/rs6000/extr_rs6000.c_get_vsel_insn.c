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
 int INSN_NOT_AVAILABLE ; 
 int UNSPEC_VSEL16QI ; 
 int UNSPEC_VSEL4SF ; 
 int UNSPEC_VSEL4SI ; 
 int UNSPEC_VSEL8HI ; 
#define  V16QImode 131 
#define  V4SFmode 130 
#define  V4SImode 129 
#define  V8HImode 128 

__attribute__((used)) static int
get_vsel_insn (enum machine_mode mode)
{
  switch (mode)
    {
    case V4SImode:
      return UNSPEC_VSEL4SI;
      break;
    case V4SFmode:
      return UNSPEC_VSEL4SF;
      break;
    case V8HImode:
      return UNSPEC_VSEL8HI;
      break;
    case V16QImode:
      return UNSPEC_VSEL16QI;
      break;
    default:
      return INSN_NOT_AVAILABLE;
      break;
    }
  return INSN_NOT_AVAILABLE;
}