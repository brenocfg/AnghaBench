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
typedef  scalar_t__ off_t ;
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  FILEIO_EINVAL ; 
 int /*<<< orphan*/  FILEIO_ESPIPE ; 
 int FIO_FD_CONSOLE_IN ; 
 int FIO_FD_CONSOLE_OUT ; 
 int FIO_FD_INVALID ; 
 scalar_t__ lseek (int,scalar_t__,int) ; 
 int /*<<< orphan*/  remote_fileio_badfd () ; 
 scalar_t__ remote_fileio_extract_int (char**,long*) ; 
 scalar_t__ remote_fileio_extract_long (char**,scalar_t__*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int remote_fileio_map_fd (int) ; 
 int /*<<< orphan*/  remote_fileio_reply (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (scalar_t__) ; 
 scalar_t__ remote_fileio_seek_flag_to_host (long,int*) ; 
 int remote_fio_no_longjmp ; 

__attribute__((used)) static void
remote_fileio_func_lseek (char *buf)
{
  long num;
  LONGEST lnum;
  int fd, flag;
  off_t offset, ret;

  /* 1. Parameter: file descriptor */
  if (remote_fileio_extract_int (&buf, &num))
    {
      remote_fileio_ioerror ();
      return;
    }
  fd = remote_fileio_map_fd ((int) num);
  if (fd == FIO_FD_INVALID)
    {
      remote_fileio_badfd ();
      return;
    }
  else if (fd == FIO_FD_CONSOLE_IN || fd == FIO_FD_CONSOLE_OUT)
    {
      remote_fileio_reply (-1, FILEIO_ESPIPE);
      return;
    }

  /* 2. Parameter: offset */
  if (remote_fileio_extract_long (&buf, &lnum))
    {
      remote_fileio_ioerror ();
      return;
    }
  offset = (off_t) lnum;
  /* 3. Parameter: flag */
  if (remote_fileio_extract_int (&buf, &num))
    {
      remote_fileio_ioerror ();
      return;
    }
  if (remote_fileio_seek_flag_to_host (num, &flag))
    {
      remote_fileio_reply (-1, FILEIO_EINVAL);
      return;
    }
  
  remote_fio_no_longjmp = 1;
  ret = lseek (fd, offset, flag);

  if (ret == (off_t) -1)
    remote_fileio_return_errno (-1);
  else
    remote_fileio_return_success (ret);
}