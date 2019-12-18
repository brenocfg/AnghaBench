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
struct line_header {char** include_dirs; struct file_entry* file_names; } ;
struct file_entry {char const* name; int dir_index; } ;

/* Variables and functions */
 scalar_t__ IS_ABSOLUTE_PATH (char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* xmalloc (int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
file_full_name (int file, struct line_header *lh, const char *comp_dir)
{
  struct file_entry *fe = &lh->file_names[file - 1];
  
  if (IS_ABSOLUTE_PATH (fe->name))
    return xstrdup (fe->name);
  else
    {
      const char *dir;
      int dir_len;
      char *full_name;

      if (fe->dir_index)
        dir = lh->include_dirs[fe->dir_index - 1];
      else
        dir = comp_dir;

      if (dir)
        {
          dir_len = strlen (dir);
          full_name = xmalloc (dir_len + 1 + strlen (fe->name) + 1);
          strcpy (full_name, dir);
          full_name[dir_len] = '/';
          strcpy (full_name + dir_len + 1, fe->name);
          return full_name;
        }
      else
        return xstrdup (fe->name);
    }
}