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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 long FILEIO_S_IFCHR ; 
 long FILEIO_S_IFDIR ; 
 long FILEIO_S_IFREG ; 
 long FILEIO_S_IRGRP ; 
 long FILEIO_S_IROTH ; 
 long FILEIO_S_IRUSR ; 
 long FILEIO_S_IWGRP ; 
 long FILEIO_S_IWOTH ; 
 long FILEIO_S_IWUSR ; 
 long FILEIO_S_IXGRP ; 
 long FILEIO_S_IXOTH ; 
 long FILEIO_S_IXUSR ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  S_IRGRP ; 
 int /*<<< orphan*/  S_IROTH ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  S_IWGRP ; 
 int /*<<< orphan*/  S_IWOTH ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  S_IXGRP ; 
 int /*<<< orphan*/  S_IXOTH ; 
 int /*<<< orphan*/  S_IXUSR ; 

__attribute__((used)) static mode_t
remote_fileio_mode_to_host (long mode, int open_call)
{
  mode_t hmode = 0;

  if (!open_call)
    {
      if (mode & FILEIO_S_IFREG)
	hmode |= S_IFREG;
      if (mode & FILEIO_S_IFDIR)
	hmode |= S_IFDIR;
      if (mode & FILEIO_S_IFCHR)
	hmode |= S_IFCHR;
    }
  if (mode & FILEIO_S_IRUSR)
    hmode |= S_IRUSR;
  if (mode & FILEIO_S_IWUSR)
    hmode |= S_IWUSR;
  if (mode & FILEIO_S_IXUSR)
    hmode |= S_IXUSR;
  if (mode & FILEIO_S_IRGRP)
    hmode |= S_IRGRP;
  if (mode & FILEIO_S_IWGRP)
    hmode |= S_IWGRP;
  if (mode & FILEIO_S_IXGRP)
    hmode |= S_IXGRP;
  if (mode & FILEIO_S_IROTH)
    hmode |= S_IROTH;
  if (mode & FILEIO_S_IWOTH)
    hmode |= S_IWOTH;
  if (mode & FILEIO_S_IXOTH)
    hmode |= S_IXOTH;
  return hmode;
}