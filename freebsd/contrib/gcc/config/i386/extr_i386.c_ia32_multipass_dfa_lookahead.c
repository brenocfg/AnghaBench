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
 scalar_t__ PROCESSOR_K6 ; 
 scalar_t__ PROCESSOR_PENTIUM ; 
 scalar_t__ PROCESSOR_PENTIUMPRO ; 
 scalar_t__ ix86_tune ; 

__attribute__((used)) static int
ia32_multipass_dfa_lookahead (void)
{
  if (ix86_tune == PROCESSOR_PENTIUM)
    return 2;

  if (ix86_tune == PROCESSOR_PENTIUMPRO
      || ix86_tune == PROCESSOR_K6)
    return 1;

  else
    return 0;
}