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
struct TYPE_3__ {char* name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ search_dirs_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* search_head ; 
 char* slash ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/ * try_open (char const*,char const*) ; 

__attribute__((used)) static FILE *
ldfile_find_command_file (const char *name, const char *extend)
{
  search_dirs_type *search;
  FILE *result;
  char buffer[1000];

  /* First try raw name.  */
  result = try_open (name, "");
  if (result == NULL)
    {
      /* Try now prefixes.  */
      for (search = search_head; search != NULL; search = search->next)
	{
	  sprintf (buffer, "%s%s%s", search->name, slash, name);

	  result = try_open (buffer, extend);
	  if (result)
	    break;
	}
    }

  return result;
}