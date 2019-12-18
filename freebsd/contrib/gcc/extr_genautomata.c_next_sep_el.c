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
 scalar_t__ ISSPACE (int) ; 
 int /*<<< orphan*/  irp ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,char const) ; 
 char* obstack_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_finish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
next_sep_el (const char **pstr, int sep, int par_flag)
{
  char *out_str;
  const char *p;
  int pars_num;
  int n_spaces;

  /* Remove leading whitespaces.  */
  while (ISSPACE ((int) **pstr))
    (*pstr)++;

  if (**pstr == '\0')
    return NULL;

  n_spaces = 0;
  for (pars_num = 0, p = *pstr; *p != '\0'; p++)
    {
      if (par_flag && *p == '(')
	pars_num++;
      else if (par_flag && *p == ')')
	pars_num--;
      else if (pars_num == 0 && *p == sep)
	break;
      if (pars_num == 0 && ISSPACE ((int) *p))
	n_spaces++;
      else
	{
	  for (; n_spaces != 0; n_spaces--)
	    obstack_1grow (&irp, p [-n_spaces]);
	  obstack_1grow (&irp, *p);
	}
    }
  obstack_1grow (&irp, '\0');
  out_str = obstack_base (&irp);
  (void) obstack_finish (&irp);

  *pstr = p;
  if (**pstr == sep)
    (*pstr)++;

  return out_str;
}