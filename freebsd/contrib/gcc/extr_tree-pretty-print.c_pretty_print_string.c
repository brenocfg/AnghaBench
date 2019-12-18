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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
pretty_print_string (pretty_printer *buffer, const char *str)
{
  if (str == NULL)
    return;

  while (*str)
    {
      switch (str[0])
	{
	case '\b':
	  pp_string (buffer, "\\b");
	  break;

	case '\f':
	  pp_string (buffer, "\\f");
	  break;

	case '\n':
	  pp_string (buffer, "\\n");
	  break;

	case '\r':
	  pp_string (buffer, "\\r");
	  break;

	case '\t':
	  pp_string (buffer, "\\t");
	  break;

	case '\v':
	  pp_string (buffer, "\\v");
	  break;

	case '\\':
	  pp_string (buffer, "\\\\");
	  break;

	case '\"':
	  pp_string (buffer, "\\\"");
	  break;

	case '\'':
	  pp_string (buffer, "\\'");
	  break;

	  /* No need to handle \0; the loop terminates on \0.  */

	case '\1':
	  pp_string (buffer, "\\1");
	  break;

	case '\2':
	  pp_string (buffer, "\\2");
	  break;

	case '\3':
	  pp_string (buffer, "\\3");
	  break;

	case '\4':
	  pp_string (buffer, "\\4");
	  break;

	case '\5':
	  pp_string (buffer, "\\5");
	  break;

	case '\6':
	  pp_string (buffer, "\\6");
	  break;

	case '\7':
	  pp_string (buffer, "\\7");
	  break;

	default:
	  pp_character (buffer, str[0]);
	  break;
	}
      str++;
    }
}