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
struct TYPE_2__ {scalar_t__* part1; int validated; } ;

/* Variables and functions */
 scalar_t__ ISIDNUM (char const) ; 
 int /*<<< orphan*/  SKIP_WHITE () ; 
 int n_switches ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,char const*,size_t) ; 
 TYPE_1__* switches ; 

__attribute__((used)) static const char *
validate_switches (const char *start)
{
  const char *p = start;
  const char *atom;
  size_t len;
  int i;
  bool suffix = false;
  bool starred = false;

#define SKIP_WHITE() do { while (*p == ' ' || *p == '\t') p++; } while (0)

next_member:
  SKIP_WHITE ();

  if (*p == '!')
    p++;

  SKIP_WHITE ();
  if (*p == '.')
    suffix = true, p++;

  atom = p;
  while (ISIDNUM (*p) || *p == '-' || *p == '+' || *p == '='
	 || *p == ',' || *p == '.' || *p == '@')
    p++;
  len = p - atom;

  if (*p == '*')
    starred = true, p++;

  SKIP_WHITE ();

  if (!suffix)
    {
      /* Mark all matching switches as valid.  */
      for (i = 0; i < n_switches; i++)
	if (!strncmp (switches[i].part1, atom, len)
	    && (starred || switches[i].part1[len] == 0))
	  switches[i].validated = 1;
    }

  if (*p) p++;
  if (*p && (p[-1] == '|' || p[-1] == '&'))
    goto next_member;

  if (*p && p[-1] == ':')
    {
      while (*p && *p != ';' && *p != '}')
	{
	  if (*p == '%')
	    {
	      p++;
	      if (*p == '{' || *p == '<')
		p = validate_switches (p+1);
	      else if (p[0] == 'W' && p[1] == '{')
		p = validate_switches (p+2);
	    }
	  else
	    p++;
	}

      if (*p) p++;
      if (*p && p[-1] == ';')
	goto next_member;
    }

  return p;
#undef SKIP_WHITE
}