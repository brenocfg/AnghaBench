#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct line_info_table {unsigned int num_files; char** dirs; char* comp_dir; TYPE_1__* files; } ;
struct TYPE_2__ {char* name; int dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ) ; 
 char* bfd_malloc (size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
concat_filename (struct line_info_table *table, unsigned int file)
{
  char *filename;

  if (file - 1 >= table->num_files)
    {
      /* FILE == 0 means unknown.  */
      if (file)
	(*_bfd_error_handler)
	  (_("Dwarf Error: mangled line number section (bad file number)."));
      return strdup ("<unknown>");
    }

  filename = table->files[file - 1].name;

  if (!IS_ABSOLUTE_PATH (filename))
    {
      char *dirname = NULL;
      char *subdirname = NULL;
      char *name;
      size_t len;

      if (table->files[file - 1].dir)
	subdirname = table->dirs[table->files[file - 1].dir - 1];

      if (!subdirname || !IS_ABSOLUTE_PATH (subdirname))
	dirname = table->comp_dir;

      if (!dirname)
	{
	  dirname = subdirname;
	  subdirname = NULL;
	}

      if (!dirname)
	return strdup (filename);

      len = strlen (dirname) + strlen (filename) + 2;

      if (subdirname)
	{
	  len += strlen (subdirname) + 1;
	  name = bfd_malloc (len);
	  if (name)
	    sprintf (name, "%s/%s/%s", dirname, subdirname, filename);
	}
      else
	{
	  name = bfd_malloc (len);
	  if (name)
	    sprintf (name, "%s/%s", dirname, filename);
	}

      return name;
    }

  return strdup (filename);
}