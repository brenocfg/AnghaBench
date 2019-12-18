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
typedef  int DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetProcessAffinityMask (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int
count_avail_process_cpus ()
{
  DWORD_PTR process_cpus;
  DWORD_PTR system_cpus;

  if (GetProcessAffinityMask (GetCurrentProcess (),
			      &process_cpus, &system_cpus))
    {
      unsigned int count;
      for (count = 0; process_cpus != 0; process_cpus >>= 1)  
	if (process_cpus & 1)
	  count++;
      return count;
    }
  return 1;
}