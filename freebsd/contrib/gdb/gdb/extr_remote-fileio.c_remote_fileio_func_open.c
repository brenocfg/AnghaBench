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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FILEIO_EISDIR ; 
 int /*<<< orphan*/  FILEIO_ENODEV ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ remote_fileio_extract_int (char**,long*) ; 
 scalar_t__ remote_fileio_extract_ptr_w_len (char**,int /*<<< orphan*/ *,int*) ; 
 int remote_fileio_fd_to_targetfd (int) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int /*<<< orphan*/  remote_fileio_mode_to_host (long,int) ; 
 int remote_fileio_oflags_to_host (long) ; 
 int /*<<< orphan*/  remote_fileio_reply (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int) ; 
 int remote_fio_no_longjmp ; 
 int remote_read_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

__attribute__((used)) static void
remote_fileio_func_open (char *buf)
{
  CORE_ADDR ptrval;
  int length, retlength;
  long num;
  int flags, fd;
  mode_t mode;
  char *pathname;
  struct stat st;

  /* 1. Parameter: Ptr to pathname / length incl. trailing zero */
  if (remote_fileio_extract_ptr_w_len (&buf, &ptrval, &length))
    {
      remote_fileio_ioerror ();
      return;
    }
  /* 2. Parameter: open flags */
  if (remote_fileio_extract_int (&buf, &num))
    {
      remote_fileio_ioerror ();
      return;
    }
  flags = remote_fileio_oflags_to_host (num);
  /* 3. Parameter: open mode */
  if (remote_fileio_extract_int (&buf, &num))
    {
      remote_fileio_ioerror ();
      return;
    }
  mode = remote_fileio_mode_to_host (num, 1);

  /* Request pathname using 'm' packet */
  pathname = alloca (length);
  retlength = remote_read_bytes (ptrval, pathname, length);
  if (retlength != length)
    {
      remote_fileio_ioerror ();
      return;
    }

  /* Check if pathname exists and is not a regular file or directory.  If so,
     return an appropriate error code.  Same for trying to open directories
     for writing. */
  if (!stat (pathname, &st))
    {
      if (!S_ISREG (st.st_mode) && !S_ISDIR (st.st_mode))
	{
	  remote_fileio_reply (-1, FILEIO_ENODEV);
	  return;
	}
      if (S_ISDIR (st.st_mode)
	  && ((flags & O_WRONLY) == O_WRONLY || (flags & O_RDWR) == O_RDWR))
	{
	  remote_fileio_reply (-1, FILEIO_EISDIR);
	  return;
	}
    }

  remote_fio_no_longjmp = 1;
  fd = open (pathname, flags, mode);
  if (fd < 0)
    {
      remote_fileio_return_errno (-1);
      return;
    }

  fd = remote_fileio_fd_to_targetfd (fd);
  remote_fileio_return_success (fd);
}