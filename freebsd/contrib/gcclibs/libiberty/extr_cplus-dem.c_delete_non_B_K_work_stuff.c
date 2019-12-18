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
struct work_stuff {int ntmpl_args; int /*<<< orphan*/ * previous_argument; scalar_t__* tmpl_argvec; scalar_t__ typevec_size; int /*<<< orphan*/ * typevec; } ;

/* Variables and functions */
 int /*<<< orphan*/  forget_types (struct work_stuff*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  string_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
delete_non_B_K_work_stuff (struct work_stuff *work)
{
  /* Discard the remembered types, if any.  */

  forget_types (work);
  if (work -> typevec != NULL)
    {
      free ((char *) work -> typevec);
      work -> typevec = NULL;
      work -> typevec_size = 0;
    }
  if (work->tmpl_argvec)
    {
      int i;

      for (i = 0; i < work->ntmpl_args; i++)
	if (work->tmpl_argvec[i])
	  free ((char*) work->tmpl_argvec[i]);

      free ((char*) work->tmpl_argvec);
      work->tmpl_argvec = NULL;
    }
  if (work->previous_argument)
    {
      string_delete (work->previous_argument);
      free ((char*) work->previous_argument);
      work->previous_argument = NULL;
    }
}