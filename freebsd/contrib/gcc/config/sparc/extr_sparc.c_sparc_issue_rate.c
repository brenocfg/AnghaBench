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
#define  PROCESSOR_HYPERSPARC 134 
#define  PROCESSOR_NIAGARA 133 
#define  PROCESSOR_SPARCLITE86X 132 
#define  PROCESSOR_SUPERSPARC 131 
#define  PROCESSOR_ULTRASPARC 130 
#define  PROCESSOR_ULTRASPARC3 129 
#define  PROCESSOR_V9 128 
 int sparc_cpu ; 

__attribute__((used)) static int
sparc_issue_rate (void)
{
  switch (sparc_cpu)
    {
    case PROCESSOR_NIAGARA:
    default:
      return 1;
    case PROCESSOR_V9:
      /* Assume V9 processors are capable of at least dual-issue.  */
      return 2;
    case PROCESSOR_SUPERSPARC:
      return 3;
    case PROCESSOR_HYPERSPARC:
    case PROCESSOR_SPARCLITE86X:
      return 2;
    case PROCESSOR_ULTRASPARC:
    case PROCESSOR_ULTRASPARC3:
      return 4;
    }
}