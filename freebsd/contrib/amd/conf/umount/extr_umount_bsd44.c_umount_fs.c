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
typedef  int u_int ;

/* Variables and functions */
 int AMU_UMOUNT_FORCE ; 
#define  EBUSY 134 
#define  EINTR 133 
#define  EINVAL 132 
#define  EIO 131 
#define  ENOENT 130 
#define  ENOTBLK 129 
#define  ESTALE 128 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  dlog (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 int umount2_fs (char*,int) ; 
 int unmount (char*,int /*<<< orphan*/ ) ; 

int
umount_fs(char *mntdir, const char *mnttabname, u_int unmount_flags)
{
  int error;

eintr:
  error = unmount(mntdir, 0);
  if (error < 0)
    error = errno;

  switch (error) {
  case EINVAL:
  case ENOTBLK:
  case ENOENT:
    plog(XLOG_WARNING, "unmount: %s is not mounted", mntdir);
    error = 0;			/* Not really an error */
    break;

  case EINTR:
    /* not sure why this happens, but it does.  ask kirk one day... */
    dlog("%s: unmount: %m", mntdir);
    goto eintr;

#ifdef MNT2_GEN_OPT_FORCE
  case EBUSY:
  case EIO:
  case ESTALE:
    /* caller determines if forced unmounts should be used */
    if (unmount_flags & AMU_UMOUNT_FORCE) {
      error = umount2_fs(mntdir, unmount_flags);
      if (error < 0)
	error = errno;
      else
	return error;
    }
    /* fallthrough */
#endif /* MNT2_GEN_OPT_FORCE */

  default:
    dlog("%s: unmount: %m", mntdir);
    break;
  }

  return error;
}