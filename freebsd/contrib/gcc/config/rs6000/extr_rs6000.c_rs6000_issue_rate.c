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
#define  CPU_POWER4 143 
#define  CPU_POWER5 142 
#define  CPU_PPC440 141 
#define  CPU_PPC601 140 
#define  CPU_PPC603 139 
#define  CPU_PPC604 138 
#define  CPU_PPC604E 137 
#define  CPU_PPC620 136 
#define  CPU_PPC630 135 
#define  CPU_PPC7400 134 
#define  CPU_PPC7450 133 
#define  CPU_PPC750 132 
#define  CPU_PPC8540 131 
#define  CPU_RIOS1 130 
#define  CPU_RIOS2 129 
#define  CPU_RS64A 128 
 int /*<<< orphan*/  reload_completed ; 
 int rs6000_cpu_attr ; 

__attribute__((used)) static int
rs6000_issue_rate (void)
{
  /* Use issue rate of 1 for first scheduling pass to decrease degradation.  */
  if (!reload_completed)
    return 1;

  switch (rs6000_cpu_attr) {
  case CPU_RIOS1:  /* ? */
  case CPU_RS64A:
  case CPU_PPC601: /* ? */
  case CPU_PPC7450:
    return 3;
  case CPU_PPC440:
  case CPU_PPC603:
  case CPU_PPC750:
  case CPU_PPC7400:
  case CPU_PPC8540:
    return 2;
  case CPU_RIOS2:
  case CPU_PPC604:
  case CPU_PPC604E:
  case CPU_PPC620:
  case CPU_PPC630:
    return 4;
  case CPU_POWER4:
  case CPU_POWER5:
    return 5;
  default:
    return 1;
  }
}