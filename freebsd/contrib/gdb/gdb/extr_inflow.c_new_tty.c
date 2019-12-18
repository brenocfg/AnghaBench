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
 int O_NOCTTY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SIGTTOU ; 
 void SIG_IGN () ; 
 int /*<<< orphan*/  TIOCNOTTY ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  errno ; 
 char* inferior_thisrun_terminal ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  print_sys_errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,void (*) ()) ; 

void
new_tty (void)
{
  int tty;

  if (inferior_thisrun_terminal == 0)
    return;
#if !defined(__GO32__) && !defined(_WIN32)
#ifdef TIOCNOTTY
  /* Disconnect the child process from our controlling terminal.  On some
     systems (SVR4 for example), this may cause a SIGTTOU, so temporarily
     ignore SIGTTOU. */
  tty = open ("/dev/tty", O_RDWR);
  if (tty > 0)
    {
      void (*osigttou) ();

      osigttou = (void (*)()) signal (SIGTTOU, SIG_IGN);
      ioctl (tty, TIOCNOTTY, 0);
      close (tty);
      signal (SIGTTOU, osigttou);
    }
#endif

  /* Now open the specified new terminal.  */

#ifdef USE_O_NOCTTY
  tty = open (inferior_thisrun_terminal, O_RDWR | O_NOCTTY);
#else
  tty = open (inferior_thisrun_terminal, O_RDWR);
#endif
  if (tty == -1)
    {
      print_sys_errmsg (inferior_thisrun_terminal, errno);
      _exit (1);
    }

  /* Avoid use of dup2; doesn't exist on all systems.  */
  if (tty != 0)
    {
      close (0);
      dup (tty);
    }
  if (tty != 1)
    {
      close (1);
      dup (tty);
    }
  if (tty != 2)
    {
      close (2);
      dup (tty);
    }
  if (tty > 2)
    close (tty);
#endif /* !go32 && !win32 */
}