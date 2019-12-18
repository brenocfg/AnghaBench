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
typedef  int mode_t ;
typedef  int LONGEST ;

/* Variables and functions */
 int FILEIO_S_IFCHR ; 
 int FILEIO_S_IFDIR ; 
 int FILEIO_S_IFREG ; 
 int FILEIO_S_IRGRP ; 
 int FILEIO_S_IROTH ; 
 int FILEIO_S_IRUSR ; 
 int FILEIO_S_IWGRP ; 
 int FILEIO_S_IWOTH ; 
 int FILEIO_S_IWUSR ; 
 int FILEIO_S_IXGRP ; 
 int FILEIO_S_IXOTH ; 
 int FILEIO_S_IXUSR ; 
 int S_IFCHR ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 

__attribute__((used)) static LONGEST
remote_fileio_mode_to_target (mode_t mode)
{
  mode_t tmode = 0;

  if (mode & S_IFREG)
    tmode |= FILEIO_S_IFREG;
  if (mode & S_IFDIR)
    tmode |= FILEIO_S_IFDIR;
  if (mode & S_IFCHR)
    tmode |= FILEIO_S_IFCHR;
  if (mode & S_IRUSR)
    tmode |= FILEIO_S_IRUSR;
  if (mode & S_IWUSR)
    tmode |= FILEIO_S_IWUSR;
  if (mode & S_IXUSR)
    tmode |= FILEIO_S_IXUSR;
  if (mode & S_IRGRP)
    tmode |= FILEIO_S_IRGRP;
  if (mode & S_IWGRP)
    tmode |= FILEIO_S_IWGRP;
  if (mode & S_IXGRP)
    tmode |= FILEIO_S_IXGRP;
  if (mode & S_IROTH)
    tmode |= FILEIO_S_IROTH;
  if (mode & S_IWOTH)
    tmode |= FILEIO_S_IWOTH;
  if (mode & S_IXOTH)
    tmode |= FILEIO_S_IXOTH;
  return tmode;
}