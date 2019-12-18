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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  gdb_client_data ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  STOP_SIGNAL ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 char* get_prompt () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  handle_stop_sig ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
async_stop_sig (gdb_client_data arg)
{
  char *prompt = get_prompt ();
#if STOP_SIGNAL == SIGTSTP
  signal (SIGTSTP, SIG_DFL);
#if HAVE_SIGPROCMASK
  {
    sigset_t zero;

    sigemptyset (&zero);
    sigprocmask (SIG_SETMASK, &zero, 0);
  }
#elif HAVE_SIGSETMASK
  sigsetmask (0);
#endif
  kill (getpid (), SIGTSTP);
  signal (SIGTSTP, handle_stop_sig);
#else
  signal (STOP_SIGNAL, handle_stop_sig);
#endif
  printf_unfiltered ("%s", prompt);
  gdb_flush (gdb_stdout);

  /* Forget about any previous command -- null line now will do nothing.  */
  dont_repeat ();
}