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
struct fio_stat {int /*<<< orphan*/  fst_dev; } ;
typedef  scalar_t__ LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FILEIO_EACCES ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 scalar_t__ remote_fileio_extract_long (char**,scalar_t__*) ; 
 scalar_t__ remote_fileio_extract_ptr_w_len (char**,scalar_t__*,int*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int /*<<< orphan*/  remote_fileio_reply (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_stat (struct stat*,struct fio_stat*) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_uint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int remote_fileio_write_bytes (scalar_t__,char*,int) ; 
 int remote_fio_no_longjmp ; 
 int remote_read_bytes (scalar_t__,char*,int) ; 
 int stat (char*,struct stat*) ; 

__attribute__((used)) static void
remote_fileio_func_stat (char *buf)
{
  CORE_ADDR ptrval;
  int ret, length, retlength;
  char *pathname;
  LONGEST lnum;
  struct stat st;
  struct fio_stat fst;

  /* 1. Parameter: Ptr to pathname / length incl. trailing zero */
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

  /* 2. Parameter: Ptr to struct stat */
  if (remote_fileio_extract_long (&buf, &lnum))
    {
      remote_fileio_ioerror ();
      return;
    }
  ptrval = (CORE_ADDR) lnum;

  remote_fio_no_longjmp = 1;
  ret = stat (pathname, &st);

  if (ret == -1)
    {
      remote_fileio_return_errno (-1);
      return;
    }
  /* Only operate on regular files and directories */
  if (!ret && !S_ISREG (st.st_mode) && !S_ISDIR (st.st_mode))
    {
      remote_fileio_reply (-1, FILEIO_EACCES);
      return;
    }
  if (ptrval)
    {
      remote_fileio_to_fio_stat (&st, &fst);
      remote_fileio_to_fio_uint (0, fst.fst_dev);
      
      retlength = remote_fileio_write_bytes (ptrval, (char *) &fst, sizeof fst);
      if (retlength != sizeof fst)
	{
	  remote_fileio_return_errno (-1);
	  return;
	}
    }
  remote_fileio_return_success (ret);
}