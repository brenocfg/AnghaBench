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

/* Variables and functions */
#define  EACCES 148 
#define  EBADF 147 
#define  EBUSY 146 
#define  EEXIST 145 
#define  EFAULT 144 
#define  EFBIG 143 
#define  EINTR 142 
#define  EINVAL 141 
#define  EIO 140 
#define  EISDIR 139 
#define  EMFILE 138 
#define  ENAMETOOLONG 137 
#define  ENFILE 136 
#define  ENODEV 135 
#define  ENOENT 134 
#define  ENOSPC 133 
#define  ENOSYS 132 
#define  ENOTDIR 131 
#define  EPERM 130 
#define  EROFS 129 
#define  ESPIPE 128 
 int FILEIO_EACCES ; 
 int FILEIO_EBADF ; 
 int FILEIO_EBUSY ; 
 int FILEIO_EEXIST ; 
 int FILEIO_EFAULT ; 
 int FILEIO_EFBIG ; 
 int FILEIO_EINTR ; 
 int FILEIO_EINVAL ; 
 int FILEIO_EIO ; 
 int FILEIO_EISDIR ; 
 int FILEIO_EMFILE ; 
 int FILEIO_ENAMETOOLONG ; 
 int FILEIO_ENFILE ; 
 int FILEIO_ENODEV ; 
 int FILEIO_ENOENT ; 
 int FILEIO_ENOSPC ; 
 int FILEIO_ENOSYS ; 
 int FILEIO_ENOTDIR ; 
 int FILEIO_EPERM ; 
 int FILEIO_EROFS ; 
 int FILEIO_ESPIPE ; 
 int FILEIO_EUNKNOWN ; 

__attribute__((used)) static int
remote_fileio_errno_to_target (int error)
{
  switch (error)
    {
      case EPERM:
        return FILEIO_EPERM;
      case ENOENT:
        return FILEIO_ENOENT;
      case EINTR:
        return FILEIO_EINTR;
      case EIO:
        return FILEIO_EIO;
      case EBADF:
        return FILEIO_EBADF;
      case EACCES:
        return FILEIO_EACCES;
      case EFAULT:
        return FILEIO_EFAULT;
      case EBUSY:
        return FILEIO_EBUSY;
      case EEXIST:
        return FILEIO_EEXIST;
      case ENODEV:
        return FILEIO_ENODEV;
      case ENOTDIR:
        return FILEIO_ENOTDIR;
      case EISDIR:
        return FILEIO_EISDIR;
      case EINVAL:
        return FILEIO_EINVAL;
      case ENFILE:
        return FILEIO_ENFILE;
      case EMFILE:
        return FILEIO_EMFILE;
      case EFBIG:
        return FILEIO_EFBIG;
      case ENOSPC:
        return FILEIO_ENOSPC;
      case ESPIPE:
        return FILEIO_ESPIPE;
      case EROFS:
        return FILEIO_EROFS;
      case ENOSYS:
        return FILEIO_ENOSYS;
      case ENAMETOOLONG:
        return FILEIO_ENAMETOOLONG;
    }
  return FILEIO_EUNKNOWN;
}