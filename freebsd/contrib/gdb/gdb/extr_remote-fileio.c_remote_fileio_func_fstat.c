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
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct stat {int st_mode; int st_nlink; int st_blksize; scalar_t__ st_ctime; scalar_t__ st_mtime; scalar_t__ st_atime; scalar_t__ st_blocks; scalar_t__ st_size; scalar_t__ st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
struct fio_stat {int /*<<< orphan*/  fst_dev; } ;
typedef  scalar_t__ LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int FIO_FD_CONSOLE_IN ; 
 int FIO_FD_CONSOLE_OUT ; 
 int FIO_FD_INVALID ; 
 int S_IFCHR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  remote_fileio_badfd () ; 
 scalar_t__ remote_fileio_extract_int (char**,long*) ; 
 scalar_t__ remote_fileio_extract_long (char**,scalar_t__*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int remote_fileio_map_fd (int) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_stat (struct stat*,struct fio_stat*) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_uint (int,int /*<<< orphan*/ ) ; 
 int remote_fileio_write_bytes (scalar_t__,char*,int) ; 
 int remote_fio_no_longjmp ; 

__attribute__((used)) static void
remote_fileio_func_fstat (char *buf)
{
  CORE_ADDR ptrval;
  int fd, ret, retlength;
  long target_fd;
  LONGEST lnum;
  struct stat st;
  struct fio_stat fst;
  struct timeval tv;

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
  /* 2. Parameter: Ptr to struct stat */
  if (remote_fileio_extract_long (&buf, &lnum))
    {
      remote_fileio_ioerror ();
      return;
    }
  ptrval = (CORE_ADDR) lnum;

  remote_fio_no_longjmp = 1;
  if (fd == FIO_FD_CONSOLE_IN || fd == FIO_FD_CONSOLE_OUT)
    {
      remote_fileio_to_fio_uint (1, fst.fst_dev);
      st.st_mode = S_IFCHR | (fd == FIO_FD_CONSOLE_IN ? S_IRUSR : S_IWUSR);
      st.st_nlink = 1;
      st.st_uid = getuid ();
      st.st_gid = getgid ();
      st.st_rdev = 0;
      st.st_size = 0;
      st.st_blksize = 512;
#if HAVE_STRUCT_STAT_ST_BLOCKS
      st.st_blocks = 0;
#endif
      if (!gettimeofday (&tv, NULL))
	st.st_atime = st.st_mtime = st.st_ctime = tv.tv_sec;
      else
        st.st_atime = st.st_mtime = st.st_ctime = (time_t) 0;
      ret = 0;
    }
  else
    ret = fstat (fd, &st);

  if (ret == -1)
    {
      remote_fileio_return_errno (-1);
      return;
    }
  if (ptrval)
    {
      remote_fileio_to_fio_stat (&st, &fst);

      retlength = remote_fileio_write_bytes (ptrval, (char *) &fst, sizeof fst);
      if (retlength != sizeof fst)
	{
	  remote_fileio_return_errno (-1);
	  return;
	}
    }
  remote_fileio_return_success (ret);
}