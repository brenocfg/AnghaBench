#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* (* la_word_break_characters ) () ;} ;

/* Variables and functions */
 TYPE_1__* current_language ; 
 char* gdb_completer_quote_characters ; 
 scalar_t__ strchr (char*,char) ; 
 char* stub1 () ; 

char *
skip_quoted_chars (char *str, char *quotechars, char *breakchars)
{
  char quote_char = '\0';
  char *scan;

  if (quotechars == NULL)
    quotechars = gdb_completer_quote_characters;

  if (breakchars == NULL)
    breakchars = current_language->la_word_break_characters();

  for (scan = str; *scan != '\0'; scan++)
    {
      if (quote_char != '\0')
	{
	  /* Ignore everything until the matching close quote char */
	  if (*scan == quote_char)
	    {
	      /* Found matching close quote. */
	      scan++;
	      break;
	    }
	}
      else if (strchr (quotechars, *scan))
	{
	  /* Found start of a quoted string. */
	  quote_char = *scan;
	}
      else if (strchr (breakchars, *scan))
	{
	  break;
	}
    }

  return (scan);
}