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
 int /*<<< orphan*/  is_id_char (char const) ; 
 int strlen (char*) ; 
 scalar_t__ strstr (char const*,char*) ; 
 char* varargs_style_indicator ; 

__attribute__((used)) static int
other_variable_style_function (const char *ansi_header)
{
#ifdef UNPROTOIZE

  /* See if we have a stdarg function, or a function which has stdarg style
     parameters or a stdarg style return type.  */

  return strstr (ansi_header, "...") != 0;

#else /* !defined (UNPROTOIZE) */

  /* See if we have a varargs function, or a function which has varargs style
     parameters or a varargs style return type.  */

  const char *p;
  int len = strlen (varargs_style_indicator);

  for (p = ansi_header; p; )
    {
      const char *candidate;

      if ((candidate = strstr (p, varargs_style_indicator)) == 0)
	return 0;
      else
	if (!is_id_char (candidate[-1]) && !is_id_char (candidate[len]))
	  return 1;
	else
	  p = candidate + 1;
    }
  return 0;
#endif /* !defined (UNPROTOIZE) */
}