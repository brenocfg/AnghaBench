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
struct subfile {int /*<<< orphan*/  name; struct subfile* next; } ;

/* Variables and functions */
 scalar_t__ FILENAME_CMP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char*) ; 
 char* concat (char*,char*,char*,int /*<<< orphan*/ *) ; 
 struct subfile* current_subfile ; 
 int /*<<< orphan*/  start_subfile (char*,char*) ; 
 struct subfile* subfiles ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
dwarf2_start_subfile (char *filename, char *dirname)
{
  /* If the filename isn't absolute, try to match an existing subfile
     with the full pathname.  */

  if (!IS_ABSOLUTE_PATH (filename) && dirname != NULL)
    {
      struct subfile *subfile;
      char *fullname = concat (dirname, "/", filename, NULL);

      for (subfile = subfiles; subfile; subfile = subfile->next)
	{
	  if (FILENAME_CMP (subfile->name, fullname) == 0)
	    {
	      current_subfile = subfile;
	      xfree (fullname);
	      return;
	    }
	}
      xfree (fullname);
    }
  start_subfile (filename, dirname);
}