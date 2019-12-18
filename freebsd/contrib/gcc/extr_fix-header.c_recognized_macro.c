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
struct fn_decl {int dummy; } ;

/* Variables and functions */
 scalar_t__ REQUIRED (struct fn_decl*) ; 
 int /*<<< orphan*/  SET_SEEN (struct fn_decl*) ; 
#define  errno_h 130 
 struct fn_decl* lookup_std_proto (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  required_other ; 
 int /*<<< orphan*/  required_unseen_count ; 
 int seen_EXIT_FAILURE ; 
 int seen_EXIT_SUCCESS ; 
 int /*<<< orphan*/  seen_S_IFBLK ; 
 int /*<<< orphan*/  seen_S_IFCHR ; 
 int /*<<< orphan*/  seen_S_IFDIR ; 
 int /*<<< orphan*/  seen_S_IFIFO ; 
 int /*<<< orphan*/  seen_S_IFLNK ; 
 int /*<<< orphan*/  seen_S_IFREG ; 
 int /*<<< orphan*/  seen_S_ISBLK ; 
 int /*<<< orphan*/  seen_S_ISCHR ; 
 int /*<<< orphan*/  seen_S_ISDIR ; 
 int /*<<< orphan*/  seen_S_ISFIFO ; 
 int /*<<< orphan*/  seen_S_ISLNK ; 
 int /*<<< orphan*/  seen_S_ISREG ; 
 int seen_errno ; 
 int special_file_handling ; 
#define  stdlib_h 129 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
#define  sys_stat_h 128 

__attribute__((used)) static void
recognized_macro (const char *fname)
{
  /* The original include file defines fname as a macro.  */
  struct fn_decl *fn = lookup_std_proto (fname, strlen (fname));

  /* Since fname is a macro, don't require a prototype for it.  */
  if (fn)
    {
      if (REQUIRED (fn))
	required_unseen_count--;
      SET_SEEN (fn);
    }

  switch (special_file_handling)
    {
    case errno_h:
      if (strcmp (fname, "errno") == 0 && !seen_errno)
	seen_errno = 1, required_other--;
      break;
    case stdlib_h:
      if (strcmp (fname, "EXIT_FAILURE") == 0 && !seen_EXIT_FAILURE)
	seen_EXIT_FAILURE = 1, required_other--;
      if (strcmp (fname, "EXIT_SUCCESS") == 0 && !seen_EXIT_SUCCESS)
	seen_EXIT_SUCCESS = 1, required_other--;
      break;
    case sys_stat_h:
      if (fname[0] == 'S' && fname[1] == '_')
	{
	  if (strcmp (fname, "S_IFBLK") == 0) seen_S_IFBLK++;
	  else if (strcmp (fname, "S_ISBLK") == 0) seen_S_ISBLK++;
	  else if (strcmp (fname, "S_IFCHR") == 0) seen_S_IFCHR++;
	  else if (strcmp (fname, "S_ISCHR") == 0) seen_S_ISCHR++;
	  else if (strcmp (fname, "S_IFDIR") == 0) seen_S_IFDIR++;
	  else if (strcmp (fname, "S_ISDIR") == 0) seen_S_ISDIR++;
	  else if (strcmp (fname, "S_IFIFO") == 0) seen_S_IFIFO++;
	  else if (strcmp (fname, "S_ISFIFO") == 0) seen_S_ISFIFO++;
	  else if (strcmp (fname, "S_IFLNK") == 0) seen_S_IFLNK++;
	  else if (strcmp (fname, "S_ISLNK") == 0) seen_S_ISLNK++;
	  else if (strcmp (fname, "S_IFREG") == 0) seen_S_IFREG++;
	  else if (strcmp (fname, "S_ISREG") == 0) seen_S_ISREG++;
	}
      break;

    default:
      break;
    }
}