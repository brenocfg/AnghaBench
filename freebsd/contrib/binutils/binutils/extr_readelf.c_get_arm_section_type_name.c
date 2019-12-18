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

/* Variables and functions */
#define  SHT_ARM_ATTRIBUTES 130 
#define  SHT_ARM_EXIDX 129 
#define  SHT_ARM_PREEMPTMAP 128 

__attribute__((used)) static const char *
get_arm_section_type_name (unsigned int sh_type)
{
  switch (sh_type)
    {
    case SHT_ARM_EXIDX:
      return "ARM_EXIDX";
    case SHT_ARM_PREEMPTMAP:
      return "ARM_PREEMPTMAP";
    case SHT_ARM_ATTRIBUTES:
      return "ARM_ATTRIBUTES";
    default:
      break;
    }
  return NULL;
}