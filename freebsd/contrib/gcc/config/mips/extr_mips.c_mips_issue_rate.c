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
#define  PROCESSOR_OCTEON 135 
#define  PROCESSOR_R4130 134 
#define  PROCESSOR_R5400 133 
#define  PROCESSOR_R5500 132 
#define  PROCESSOR_R7000 131 
#define  PROCESSOR_R9000 130 
#define  PROCESSOR_SB1 129 
#define  PROCESSOR_SB1A 128 
 int mips_tune ; 

__attribute__((used)) static int
mips_issue_rate (void)
{
  switch (mips_tune)
    {
    case PROCESSOR_R4130:
    case PROCESSOR_R5400:
    case PROCESSOR_R5500:
    case PROCESSOR_R7000:
    case PROCESSOR_R9000:
    case PROCESSOR_OCTEON:
      return 2;

    case PROCESSOR_SB1:
    case PROCESSOR_SB1A:
      /* This is actually 4, but we get better performance if we claim 3.
	 This is partly because of unwanted speculative code motion with the
	 larger number, and partly because in most common cases we can't
	 reach the theoretical max of 4.  */
      return 3;

    default:
      return 1;
    }
}