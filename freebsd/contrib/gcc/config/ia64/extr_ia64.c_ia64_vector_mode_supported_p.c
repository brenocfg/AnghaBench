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
#define  V2SFmode 131 
#define  V2SImode 130 
#define  V4HImode 129 
#define  V8QImode 128 

__attribute__((used)) static bool
ia64_vector_mode_supported_p (enum machine_mode mode)
{
  switch (mode)
    {
    case V8QImode:
    case V4HImode:
    case V2SImode:
      return true;

    case V2SFmode:
      return true;

    default:
      return false;
    }
}