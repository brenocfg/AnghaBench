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
typedef  unsigned int sigset_t ;

/* Variables and functions */
 int NSIG ; 
 scalar_t__* pending_array ; 

int
sigpending (sigset_t *set)
{
  sigset_t pending = 0;
  int sig;

  for (sig = 0; sig < NSIG; sig++)
    if (pending_array[sig])
      pending |= 1U << sig;
  *set = pending;
  return 0;
}