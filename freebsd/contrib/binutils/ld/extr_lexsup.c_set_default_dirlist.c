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

/* Variables and functions */
 int /*<<< orphan*/  PATH_SEPARATOR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ldfile_add_library_path (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_default_dirlist (char *dirlist_ptr)
{
  char *p;

  while (1)
    {
      p = strchr (dirlist_ptr, PATH_SEPARATOR);
      if (p != NULL)
	*p = '\0';
      if (*dirlist_ptr != '\0')
	ldfile_add_library_path (dirlist_ptr, TRUE);
      if (p == NULL)
	break;
      dirlist_ptr = p + 1;
    }
}