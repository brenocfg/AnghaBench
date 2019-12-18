#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct excluded_lib {struct excluded_lib* next; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {void* no_export; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 void* TRUE ; 
 struct excluded_lib* excluded_libs ; 
 char* lbasename (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
check_excluded_libs (bfd *abfd)
{
  struct excluded_lib *lib = excluded_libs;

  while (lib)
    {
      int len = strlen (lib->name);
      const char *filename = lbasename (abfd->filename);

      if (strcmp (lib->name, "ALL") == 0)
	{
	  abfd->no_export = TRUE;
	  return;
	}

      if (strncmp (lib->name, filename, len) == 0
	  && (filename[len] == '\0'
	      || (filename[len] == '.' && filename[len + 1] == 'a'
		  && filename[len + 2] == '\0')))
	{
	  abfd->no_export = TRUE;
	  return;
	}

      lib = lib->next;
    }
}