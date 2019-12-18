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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int IN_SIGTRAMP (scalar_t__,char*) ; 
 scalar_t__ SIGTRAMP_END (scalar_t__) ; 
 scalar_t__ SIGTRAMP_START (scalar_t__) ; 
 scalar_t__ SIGTRAMP_START_P () ; 
 scalar_t__ strcmp (char*,char*) ; 

int
legacy_pc_in_sigtramp (CORE_ADDR pc, char *name)
{
#if !defined (IN_SIGTRAMP)
  if (SIGTRAMP_START_P ())
    return (pc) >= SIGTRAMP_START (pc) && (pc) < SIGTRAMP_END (pc);
  else
    return name && strcmp ("_sigtramp", name) == 0;
#else
  return IN_SIGTRAMP (pc, name);
#endif
}