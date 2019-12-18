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
 int NUM_SIGS ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/ * initial_action ; 
 scalar_t__ initial_handler (int) ; 
 int /*<<< orphan*/  sigaction (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int* sigs ; 
 scalar_t__ sigs_trapped ; 

__attribute__((used)) static void
untrapsig (int s)
{
  int i;

  if (sigs_trapped)
    for (i = 0;  i < NUM_SIGS;  i++)
      if ((! s || sigs[i] == s)  &&  initial_handler (i) != SIG_IGN)
	{
#if HAVE_SIGACTION
	  sigaction (sigs[i], &initial_action[i], 0);
#else
	  signal (sigs[i], initial_action[i]);
#endif
	}
}