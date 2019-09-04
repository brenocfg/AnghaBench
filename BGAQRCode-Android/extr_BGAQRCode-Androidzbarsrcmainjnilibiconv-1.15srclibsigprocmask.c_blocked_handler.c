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
 int NSIG ; 
 int* pending_array ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

__attribute__((used)) static void
blocked_handler (int sig)
{
  /* Reinstall the handler, in case the signal occurs multiple times
     while blocked.  There is an inherent race where an asynchronous
     signal in between when the kernel uninstalled the handler and
     when we reinstall it will trigger the default handler; oh
     well.  */
  signal (sig, blocked_handler);
  if (sig >= 0 && sig < NSIG)
    pending_array[sig] = 1;
}