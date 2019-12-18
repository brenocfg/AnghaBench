#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* valid_pch ) (TYPE_3__*,char const*,int) ;} ;
struct TYPE_12__ {TYPE_2__* line_table; TYPE_1__ cb; } ;
typedef  TYPE_3__ cpp_reader ;
struct TYPE_13__ {char* path; int fd; } ;
typedef  TYPE_4__ _cpp_file ;
struct TYPE_11__ {unsigned int depth; } ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char,char const*) ; 
 scalar_t__ open_file (TYPE_4__*) ; 
 int /*<<< orphan*/  print_include_names ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (TYPE_3__*,char const*,int) ; 

__attribute__((used)) static bool
validate_pch (cpp_reader *pfile, _cpp_file *file, const char *pchname)
{
  const char *saved_path = file->path;
  bool valid = false;

  file->path = pchname;
  if (open_file (file))
    {
      valid = 1 & pfile->cb.valid_pch (pfile, pchname, file->fd);

      if (!valid)
	{
	  close (file->fd);
	  file->fd = -1;
	}

      if (CPP_OPTION (pfile, print_include_names))
	{
	  unsigned int i;
	  for (i = 1; i < pfile->line_table->depth; i++)
	    putc ('.', stderr);
	  fprintf (stderr, "%c %s\n",
		   valid ? '!' : 'x', pchname);
	}
    }

  file->path = saved_path;
  return valid;
}