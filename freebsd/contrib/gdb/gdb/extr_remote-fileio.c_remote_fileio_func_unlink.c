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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FILEIO_ENODEV ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 scalar_t__ remote_fileio_extract_ptr_w_len (char**,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int /*<<< orphan*/  remote_fileio_reply (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int) ; 
 int remote_fio_no_longjmp ; 
 int remote_read_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int unlink (char*) ; 

__attribute__((used)) static void
remote_fileio_func_unlink (char *buf)
{
  CORE_ADDR ptrval;
  int length, retlength;
  char *pathname;
  int ret;
  struct stat st;

  /* Parameter: Ptr to pathname / length incl. trailing zero */
  if (remote_fileio_extract_ptr_w_len (&buf, &ptrval, &length))
    {
      remote_fileio_ioerror ();
      return;
    }
  /* Request pathname using 'm' packet */
  pathname = alloca (length);
  retlength = remote_read_bytes (ptrval, pathname, length);
  if (retlength != length)
    {
      remote_fileio_ioerror ();
      return;
    }

  /* Only operate on regular files (and directories, which allows to return
     the correct return code) */
  if (!stat (pathname, &st) && !S_ISREG (st.st_mode) && !S_ISDIR (st.st_mode))
    {
      remote_fileio_reply (-1, FILEIO_ENODEV);
      return;
    }

  remote_fio_no_longjmp = 1;
  ret = unlink (pathname);

  if (ret == -1)
    remote_fileio_return_errno (-1);
  else
    remote_fileio_return_success (ret);
}