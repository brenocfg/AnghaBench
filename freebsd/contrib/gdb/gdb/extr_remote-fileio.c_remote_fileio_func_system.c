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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FILEIO_EPERM ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 char* alloca (int) ; 
 scalar_t__ remote_fileio_extract_ptr_w_len (char**,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int /*<<< orphan*/  remote_fileio_reply (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int /*<<< orphan*/ ) ; 
 int remote_fio_no_longjmp ; 
 int /*<<< orphan*/  remote_fio_system_call_allowed ; 
 int remote_read_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int system (char*) ; 

__attribute__((used)) static void
remote_fileio_func_system (char *buf)
{
  CORE_ADDR ptrval;
  int ret, length, retlength;
  char *cmdline;

  /* Check if system(3) has been explicitely allowed using the
     `set remote system-call-allowed 1' command.  If not, return
     EPERM */
  if (!remote_fio_system_call_allowed)
    {
      remote_fileio_reply (-1, FILEIO_EPERM);
      return;
    }

  /* Parameter: Ptr to commandline / length incl. trailing zero */
  if (remote_fileio_extract_ptr_w_len (&buf, &ptrval, &length))
    {
      remote_fileio_ioerror ();
      return;
    }
  /* Request commandline using 'm' packet */
  cmdline = alloca (length);
  retlength = remote_read_bytes (ptrval, cmdline, length);
  if (retlength != length)
    {
      remote_fileio_ioerror ();
      return;
    }

  remote_fio_no_longjmp = 1;
  ret = system (cmdline);

  if (ret == -1)
    remote_fileio_return_errno (-1);
  else
    remote_fileio_return_success (WEXITSTATUS (ret));
}