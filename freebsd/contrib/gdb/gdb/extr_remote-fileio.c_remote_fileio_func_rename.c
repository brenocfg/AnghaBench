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
 scalar_t__ EACCES ; 
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EISDIR ; 
 scalar_t__ ENOTEMPTY ; 
 int /*<<< orphan*/  FILEIO_EACCES ; 
 int /*<<< orphan*/  PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  cygwin_conv_to_full_posix_path (char*,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ remote_fileio_extract_ptr_w_len (char**,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  remote_fileio_ioerror () ; 
 int /*<<< orphan*/  remote_fileio_reply (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_return_errno (int) ; 
 int /*<<< orphan*/  remote_fileio_return_success (int) ; 
 int remote_fio_no_longjmp ; 
 int remote_read_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int rename (char*,char*) ; 
 int stat (char*,struct stat*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void
remote_fileio_func_rename (char *buf)
{
  CORE_ADDR ptrval;
  int length, retlength;
  char *oldpath, *newpath;
  int ret, of, nf;
  struct stat ost, nst;

  /* 1. Parameter: Ptr to oldpath / length incl. trailing zero */
  if (remote_fileio_extract_ptr_w_len (&buf, &ptrval, &length))
    {
      remote_fileio_ioerror ();
      return;
    }
  /* Request oldpath using 'm' packet */
  oldpath = alloca (length);
  retlength = remote_read_bytes (ptrval, oldpath, length);
  if (retlength != length)
    {
      remote_fileio_ioerror ();
      return;
    }
  /* 2. Parameter: Ptr to newpath / length incl. trailing zero */
  if (remote_fileio_extract_ptr_w_len (&buf, &ptrval, &length))
    {
      remote_fileio_ioerror ();
      return;
    }
  /* Request newpath using 'm' packet */
  newpath = alloca (length);
  retlength = remote_read_bytes (ptrval, newpath, length);
  if (retlength != length)
    {
      remote_fileio_ioerror ();
      return;
    }
  
  /* Only operate on regular files and directories */
  of = stat (oldpath, &ost);
  nf = stat (newpath, &nst);
  if ((!of && !S_ISREG (ost.st_mode) && !S_ISDIR (ost.st_mode))
      || (!nf && !S_ISREG (nst.st_mode) && !S_ISDIR (nst.st_mode)))
    {
      remote_fileio_reply (-1, FILEIO_EACCES);
      return;
    }

  remote_fio_no_longjmp = 1;
  ret = rename (oldpath, newpath);

  if (ret == -1)
    {
      /* Special case: newpath is a non-empty directory.  Some systems
         return ENOTEMPTY, some return EEXIST.  We coerce that to be
	 always EEXIST. */
      if (errno == ENOTEMPTY)
        errno = EEXIST;
#ifdef __CYGWIN__
      /* Workaround some Cygwin problems with correct errnos. */
      if (errno == EACCES)
        {
	  if (!of && !nf && S_ISDIR (nst.st_mode))
	    {
	      if (S_ISREG (ost.st_mode))
		errno = EISDIR;
	      else
		{
		  char oldfullpath[PATH_MAX + 1];
		  char newfullpath[PATH_MAX + 1];
		  int len;

		  cygwin_conv_to_full_posix_path (oldpath, oldfullpath);
		  cygwin_conv_to_full_posix_path (newpath, newfullpath);
		  len = strlen (oldfullpath);
		  if (newfullpath[len] == '/'
		      && !strncmp (oldfullpath, newfullpath, len))
		    errno = EINVAL;
		  else
		    errno = EEXIST;
		}
	    }
	}
#endif

      remote_fileio_return_errno (-1);
    }
  else
    remote_fileio_return_success (ret);
}