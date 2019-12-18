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
struct sigaction {void (* sa_handler ) (int) ;int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

void
setup_sighandler(int signum, void (*handler)(int))
{
#ifdef HAVE_SIGACTION
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_flags = 0;		/* unnecessary */
  sa.sa_handler = handler;
  sigemptyset(&(sa.sa_mask));	/* probably unnecessary too */
  sigaddset(&(sa.sa_mask), signum);
  sigaction(signum, &sa, NULL);
#else /* not HAVE_SIGACTION */
  (void) signal(signum, handler);
#endif /* not HAVE_SIGACTION */
}