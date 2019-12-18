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
#define  PROCESSOR_AMDFAM10 138 
#define  PROCESSOR_ATHLON 137 
#define  PROCESSOR_CORE2 136 
#define  PROCESSOR_GENERIC32 135 
#define  PROCESSOR_GENERIC64 134 
#define  PROCESSOR_K6 133 
#define  PROCESSOR_K8 132 
#define  PROCESSOR_NOCONA 131 
#define  PROCESSOR_PENTIUM 130 
#define  PROCESSOR_PENTIUM4 129 
#define  PROCESSOR_PENTIUMPRO 128 
 int ix86_tune ; 

__attribute__((used)) static int
ix86_issue_rate (void)
{
  switch (ix86_tune)
    {
    case PROCESSOR_PENTIUM:
    case PROCESSOR_K6:
      return 2;

    case PROCESSOR_PENTIUMPRO:
    case PROCESSOR_PENTIUM4:
    case PROCESSOR_ATHLON:
    case PROCESSOR_K8:
    case PROCESSOR_AMDFAM10:
    case PROCESSOR_NOCONA:
    case PROCESSOR_GENERIC32:
    case PROCESSOR_GENERIC64:
      return 3;

    case PROCESSOR_CORE2:
      return 4;

    default:
      return 1;
    }
}