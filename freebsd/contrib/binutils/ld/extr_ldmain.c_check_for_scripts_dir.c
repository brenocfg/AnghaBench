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
typedef  int bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ldfile_add_library_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 size_t strlen (char*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
check_for_scripts_dir (char *dir)
{
  size_t dirlen;
  char *buf;
  struct stat s;
  bfd_boolean res;

  dirlen = strlen (dir);
  /* sizeof counts the terminating NUL.  */
  buf = xmalloc (dirlen + sizeof ("/ldscripts"));
  sprintf (buf, "%s/ldscripts", dir);

  res = stat (buf, &s) == 0 && S_ISDIR (s.st_mode);
  free (buf);
  if (res)
    ldfile_add_library_path (dir, FALSE);
  return res;
}