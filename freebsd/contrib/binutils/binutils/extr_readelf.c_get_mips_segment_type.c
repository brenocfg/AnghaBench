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
#define  PT_MIPS_OPTIONS 130 
#define  PT_MIPS_REGINFO 129 
#define  PT_MIPS_RTPROC 128 

__attribute__((used)) static const char *
get_mips_segment_type (unsigned long type)
{
  switch (type)
    {
    case PT_MIPS_REGINFO:
      return "REGINFO";
    case PT_MIPS_RTPROC:
      return "RTPROC";
    case PT_MIPS_OPTIONS:
      return "OPTIONS";
    default:
      break;
    }

  return NULL;
}