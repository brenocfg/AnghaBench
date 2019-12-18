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
struct work_stuff {int nrepeats; int /*<<< orphan*/  forgetting_types; int /*<<< orphan*/ * previous_argument; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 int demangle_args (struct work_stuff*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  string_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
demangle_nested_args (struct work_stuff *work, const char **mangled,
                      string *declp)
{
  string* saved_previous_argument;
  int result;
  int saved_nrepeats;

  /* The G++ name-mangling algorithm does not remember types on nested
     argument lists, unless -fsquangling is used, and in that case the
     type vector updated by remember_type is not used.  So, we turn
     off remembering of types here.  */
  ++work->forgetting_types;

  /* For the repeat codes used with -fsquangling, we must keep track of
     the last argument.  */
  saved_previous_argument = work->previous_argument;
  saved_nrepeats = work->nrepeats;
  work->previous_argument = 0;
  work->nrepeats = 0;

  /* Actually demangle the arguments.  */
  result = demangle_args (work, mangled, declp);

  /* Restore the previous_argument field.  */
  if (work->previous_argument)
    {
      string_delete (work->previous_argument);
      free ((char *) work->previous_argument);
    }
  work->previous_argument = saved_previous_argument;
  --work->forgetting_types;
  work->nrepeats = saved_nrepeats;

  return result;
}