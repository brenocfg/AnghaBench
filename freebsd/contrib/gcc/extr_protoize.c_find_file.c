#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* time_t ;
struct stat {void* st_mtime; } ;
struct TYPE_6__ {TYPE_2__* fip; } ;
typedef  TYPE_1__ hash_table_entry ;
struct TYPE_7__ {void* mtime; int /*<<< orphan*/ * defs_decs; TYPE_1__* hash_entry; } ;
typedef  TYPE_2__ file_info ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  filename_primary ; 
 TYPE_1__* lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pname ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,char const*) ; 
 int stat (char const*,struct stat*) ; 
 TYPE_2__* xmalloc (int) ; 
 int /*<<< orphan*/  xstrerror (int) ; 

__attribute__((used)) static file_info *
find_file (const char *filename, int do_not_stat)
{
  hash_table_entry *hash_entry_p;

  hash_entry_p = lookup (filename_primary, filename);
  if (hash_entry_p->fip)
    return hash_entry_p->fip;
  else
    {
      struct stat stat_buf;
      file_info *file_p = xmalloc (sizeof (file_info));

      /* If we cannot get status on any given source file, give a warning
	 and then just set its time of last modification to infinity.  */

      if (do_not_stat)
	stat_buf.st_mtime = (time_t) 0;
      else
	{
	  if (stat (filename, &stat_buf) == -1)
	    {
	      int errno_val = errno;
	      notice ("%s: %s: can't get status: %s\n",
		      pname, shortpath (NULL, filename),
		      xstrerror (errno_val));
	      stat_buf.st_mtime = (time_t) -1;
	    }
	}

      hash_entry_p->fip = file_p;
      file_p->hash_entry = hash_entry_p;
      file_p->defs_decs = NULL;
      file_p->mtime = stat_buf.st_mtime;
      return file_p;
    }
}