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
 scalar_t__ MEP_VLIW64 ; 
 int /*<<< orphan*/  mep_check_parallel32_scheduling () ; 
 int /*<<< orphan*/  mep_check_parallel64_scheduling () ; 

__attribute__((used)) static void
mep_check_parallel_scheduling (void)
{
  /* This is where we will eventually read the config information
     and choose which scheduling checking function to call.  */   
  if (MEP_VLIW64)
    mep_check_parallel64_scheduling ();
  else
    mep_check_parallel32_scheduling ();
}