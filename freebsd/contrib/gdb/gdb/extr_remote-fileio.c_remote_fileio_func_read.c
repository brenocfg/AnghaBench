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
typedef  int off_t ;
typedef  scalar_t__ LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
#define  FIO_FD_CONSOLE_IN 129 
#define  FIO_FD_CONSOLE_OUT 128 
 int FIO_FD_INVALID ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  gdb_stdtargin ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int read (int,char*,size_t) ; 
 int /*<<< orphan*/  remote_fileio_badfd () ; 
 scalar_t__ remote_fileio_extract_int (char**,long*) ; 
 scalar_t__ remote_fileio_extract_long (char**,scalar_t__*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int remote_fileio_map_fd (int) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int) ; 
 int remote_fileio_write_bytes (scalar_t__,char*,int) ; 
 int remote_fio_no_longjmp ; 
 int ui_file_read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (size_t) ; 

__attribute__((used)) static void
remote_fileio_func_read (char *buf)
{
  long target_fd, num;
  LONGEST lnum;
  CORE_ADDR ptrval;
  int fd, ret, retlength;
  char *buffer;
  size_t length;
  off_t old_offset, new_offset;

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

  switch (fd)
    {
      case FIO_FD_CONSOLE_OUT:
	remote_fileio_badfd ();
	return;
      case FIO_FD_CONSOLE_IN:
	{
	  static char *remaining_buf = NULL;
	  static int remaining_length = 0;

	  buffer = (char *) xmalloc (32768);
	  if (remaining_buf)
	    {
	      remote_fio_no_longjmp = 1;
	      if (remaining_length > length)
		{
		  memcpy (buffer, remaining_buf, length);
		  memmove (remaining_buf, remaining_buf + length,
			   remaining_length - length);
		  remaining_length -= length;
		  ret = length;
		}
	      else
		{
		  memcpy (buffer, remaining_buf, remaining_length);
		  xfree (remaining_buf);
		  remaining_buf = NULL;
		  ret = remaining_length;
		}
	    }
	  else
	    {
	      ret = ui_file_read (gdb_stdtargin, buffer, 32767);
	      remote_fio_no_longjmp = 1;
	      if (ret > 0 && (size_t)ret > length)
		{
		  remaining_buf = (char *) xmalloc (ret - length);
		  remaining_length = ret - length;
		  memcpy (remaining_buf, buffer + length, remaining_length);
		  ret = length;
		}
	    }
	}
	break;
      default:
	buffer = (char *) xmalloc (length);
	/* POSIX defines EINTR behaviour of read in a weird way.  It's allowed
	   for read() to return -1 even if "some" bytes have been read.  It
	   has been corrected in SUSv2 but that doesn't help us much...
	   Therefore a complete solution must check how many bytes have been
	   read on EINTR to return a more reliable value to the target */
	old_offset = lseek (fd, 0, SEEK_CUR);
	remote_fio_no_longjmp = 1;
	ret = read (fd, buffer, length);
	if (ret < 0 && errno == EINTR)
	  {
	    new_offset = lseek (fd, 0, SEEK_CUR);
	    /* If some data has been read, return the number of bytes read.
	       The Ctrl-C flag is set in remote_fileio_reply() anyway */
	    if (old_offset != new_offset)
	      ret = new_offset - old_offset;
	  }
	break;
    }

  if (ret > 0)
    {
      retlength = remote_fileio_write_bytes (ptrval, buffer, ret);
      if (retlength != ret)
	ret = -1; /* errno has been set to EIO in remote_fileio_write_bytes() */
    }

  if (ret < 0)
    remote_fileio_return_errno (-1);
  else
    remote_fileio_return_success (ret);

  xfree (buffer);
}