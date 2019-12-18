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
 scalar_t__ PROCESSOR_2084_Z990 ; 
 scalar_t__ PROCESSOR_2094_Z9_109 ; 
 scalar_t__ s390_tune ; 

__attribute__((used)) static int
s390_issue_rate (void)
{
  if (s390_tune == PROCESSOR_2084_Z990
      || s390_tune == PROCESSOR_2094_Z9_109)
    return 3;
  return 1;
}