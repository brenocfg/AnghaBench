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
struct pex_obj {int /*<<< orphan*/ * tempbase; } ;

/* Variables and functions */
 int PEX_SUFFIX ; 
 int /*<<< orphan*/  close (int) ; 
 char* concat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* make_temp_file (char*) ; 
 int mkstemps (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 char* xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
temp_file (struct pex_obj *obj, int flags, char *name)
{
  if (name == NULL)
    {
      if (obj->tempbase == NULL)
        {
          name = make_temp_file (NULL);
        }
      else
        {
          int len = strlen (obj->tempbase);
          int out;

          if (len >= 6
              && strcmp (obj->tempbase + len - 6, "XXXXXX") == 0)
            name = xstrdup (obj->tempbase);
          else
            name = concat (obj->tempbase, "XXXXXX", NULL);

          out = mkstemps (name, 0);
          if (out < 0)
            {
              free (name);
              return NULL;
            }

          /* This isn't obj->funcs->close because we got the
             descriptor from mkstemps, not from a function in
             obj->funcs.  Calling close here is just like what
             make_temp_file does.  */
          close (out);
        }
    }
  else if ((flags & PEX_SUFFIX) != 0)
    {
      if (obj->tempbase == NULL)
        name = make_temp_file (name);
      else
        name = concat (obj->tempbase, name, NULL);
    }

  return name;
}