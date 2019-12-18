#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* dir; int /*<<< orphan*/ * args; void* main; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freadsym (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int fscanf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pfgets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  temporary_firstobj ; 
 int /*<<< orphan*/  temporary_obstack ; 
 int tlink_verbose ; 

__attribute__((used)) static void
read_repo_file (file *f)
{
  char c;
  FILE *stream = fopen (f->key, "r");

  if (tlink_verbose >= 2)
    fprintf (stderr, "%s", _("collect: reading %s\n"), f->key);

  while (fscanf (stream, "%c ", &c) == 1)
    {
      switch (c)
	{
	case 'A':
	  f->args = pfgets (stream);
	  break;
	case 'D':
	  f->dir = pfgets (stream);
	  break;
	case 'M':
	  f->main = pfgets (stream);
	  break;
	case 'P':
	  freadsym (stream, f, 2);
	  break;
	case 'C':
	  freadsym (stream, f, 1);
	  break;
	case 'O':
	  freadsym (stream, f, 0);
	  break;
	}
      obstack_free (&temporary_obstack, temporary_firstobj);
    }
  fclose (stream);
  if (f->args == NULL)
    f->args = getenv ("COLLECT_GCC_OPTIONS");
  if (f->dir == NULL)
    f->dir = ".";
}