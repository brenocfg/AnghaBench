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
 int /*<<< orphan*/  ISALNUM (char const) ; 
 scalar_t__ do_spec_1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* eval_spec_function (char*,char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  processing_spec_function ; 
 char* save_string (char const*,int) ; 

__attribute__((used)) static const char *
handle_spec_function (const char *p)
{
  char *func, *args;
  const char *endp, *funcval;
  int count;

  processing_spec_function++;

  /* Get the function name.  */
  for (endp = p; *endp != '\0'; endp++)
    {
      if (*endp == '(')		/* ) */
        break;
      /* Only allow [A-Za-z0-9], -, and _ in function names.  */
      if (!ISALNUM (*endp) && !(*endp == '-' || *endp == '_'))
	fatal ("malformed spec function name");
    }
  if (*endp != '(')		/* ) */
    fatal ("no arguments for spec function");
  func = save_string (p, endp - p);
  p = ++endp;

  /* Get the arguments.  */
  for (count = 0; *endp != '\0'; endp++)
    {
      /* ( */
      if (*endp == ')')
	{
	  if (count == 0)
	    break;
	  count--;
	}
      else if (*endp == '(')	/* ) */
	count++;
    }
  /* ( */
  if (*endp != ')')
    fatal ("malformed spec function arguments");
  args = save_string (p, endp - p);
  p = ++endp;

  /* p now points to just past the end of the spec function expression.  */

  funcval = eval_spec_function (func, args);
  if (funcval != NULL && do_spec_1 (funcval, 0, NULL) < 0)
    p = NULL;

  free (func);
  free (args);

  processing_spec_function--;

  return p;
}