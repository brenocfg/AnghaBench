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
struct pex_obj {scalar_t__ count; scalar_t__ next_input; char* next_input_name; int next_input_name_allocated; int /*<<< orphan*/ * input_file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int PEX_BINARY_OUTPUT ; 
 scalar_t__ STDIN_FILE_NO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* temp_file (struct pex_obj*,int,char*) ; 

FILE *
pex_input_file (struct pex_obj *obj, int flags, const char *in_name)
{
  char *name = (char *) in_name;
  FILE *f;

  /* This must be called before the first pipeline stage is run, and
     there must not have been any other input selected.  */
  if (obj->count != 0
      || (obj->next_input >= 0 && obj->next_input != STDIN_FILE_NO)
      || obj->next_input_name)
    {
      errno = EINVAL;
      return NULL;
    }

  name = temp_file (obj, flags, name);
  if (! name)
    return NULL;

  f = fopen (name, (flags & PEX_BINARY_OUTPUT) ? "wb" : "w");
  if (! f)
    {
      free (name);
      return NULL;
    }

  obj->input_file = f;
  obj->next_input_name = name;
  obj->next_input_name_allocated = (name != in_name);

  return f;
}