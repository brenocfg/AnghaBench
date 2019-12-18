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
typedef  scalar_t__ LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EBADF ; 
#define  FIO_FD_CONSOLE_IN 129 
#define  FIO_FD_CONSOLE_OUT 128 
 int FIO_FD_INVALID ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdtarg ; 
 int /*<<< orphan*/  gdb_stdtargerr ; 
 int /*<<< orphan*/  remote_fileio_badfd () ; 
 scalar_t__ remote_fileio_extract_int (char**,long*) ; 
 scalar_t__ remote_fileio_extract_long (char**,scalar_t__*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int remote_fileio_map_fd (int) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int) ; 
 int remote_fio_no_longjmp ; 
 int remote_read_bytes (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  ui_file_write (int /*<<< orphan*/ ,char*,size_t) ; 
 int write (int,char*,size_t) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (size_t) ; 

__attribute__((used)) static void
remote_fileio_func_write (char *buf)
{
  long target_fd, num;
  LONGEST lnum;
  CORE_ADDR ptrval;
  int fd, ret, retlength;
  char *buffer;
  size_t length;

  /* 1. Parameter: file descriptor */
  if (remote_fileio_extract_int (&buf, &target_fd))
    {
      remote_fileio_ioerror ();
      return;
    }
  fd = remote_fileio_map_fd ((int) target_fd);
  if (fd == FIO_FD_INVALID)
    {
      remote_fileio_badfd ();
      return;
    }
  /* 2. Parameter: buffer pointer */
  if (remote_fileio_extract_long (&buf, &lnum))
    {
      remote_fileio_ioerror ();
      return;
    }
  ptrval = (CORE_ADDR) lnum;
  /* 3. Parameter: buffer length */
  if (remote_fileio_extract_int (&buf, &num))
    {
      remote_fileio_ioerror ();
      return;
    }
  length = (size_t) num;
    
  buffer = (char *) xmalloc (length);
  retlength = remote_read_bytes (ptrval, buffer, length);
  if (retlength != length)
    {
      xfree (buffer);
      remote_fileio_ioerror ();
      return;
    }

  remote_fio_no_longjmp = 1;
  switch (fd)
    {
      case FIO_FD_CONSOLE_IN:
	remote_fileio_badfd ();
	return;
      case FIO_FD_CONSOLE_OUT:
	ui_file_write (target_fd == 1 ? gdb_stdtarg : gdb_stdtargerr, buffer,
		       length);
	gdb_flush (target_fd == 1 ? gdb_stdtarg : gdb_stdtargerr);
	ret = length;
	break;
      default:
	ret = write (fd, buffer, length);
	if (ret < 0 && errno == EACCES)
	  errno = EBADF; /* Cygwin returns EACCESS when writing to a R/O file.*/
	break;
    }

  if (ret < 0)
    remote_fileio_return_errno (-1);
  else
    remote_fileio_return_success (ret);

  xfree (buffer);
}