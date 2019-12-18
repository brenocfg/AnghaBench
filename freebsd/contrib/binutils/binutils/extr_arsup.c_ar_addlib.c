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
struct list {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  ar_addlib_doer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  map_over_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct list*) ; 
 int /*<<< orphan*/  maybequit () ; 
 int /*<<< orphan*/ * obfd ; 
 int /*<<< orphan*/ * open_inarch (char*,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 

void
ar_addlib (char *name, struct list *list)
{
  if (obfd == NULL)
    {
      fprintf (stderr, _("%s: no output archive specified yet\n"), program_name);
      maybequit ();
    }
  else
    {
      bfd *arch;

      arch = open_inarch (name, (char *) NULL);
      if (arch != NULL)
	map_over_list (arch, ar_addlib_doer, list);

      /* Don't close the bfd, since it will make the elements disappear.  */
    }
}