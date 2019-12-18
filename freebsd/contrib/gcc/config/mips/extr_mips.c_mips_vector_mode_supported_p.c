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
 int TARGET_DSP ; 
 int TARGET_PAIRED_SINGLE_FLOAT ; 
#define  V2HImode 130 
#define  V2SFmode 129 
#define  V4QImode 128 

__attribute__((used)) static bool
mips_vector_mode_supported_p (enum machine_mode mode)
{
  switch (mode)
    {
    case V2SFmode:
      return TARGET_PAIRED_SINGLE_FLOAT;

    case V2HImode:
    case V4QImode:
      return TARGET_DSP;

    default:
      return false;
    }
}