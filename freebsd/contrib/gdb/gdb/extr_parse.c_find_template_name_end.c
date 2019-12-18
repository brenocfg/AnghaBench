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

char *
find_template_name_end (char *p)
{
  int depth = 1;
  int just_seen_right = 0;
  int just_seen_colon = 0;
  int just_seen_space = 0;

  if (!p || (*p != '<'))
    return 0;

  while (*++p)
    {
      switch (*p)
	{
	case '\'':
	case '\"':
	case '{':
	case '}':
	  /* In future, may want to allow these?? */
	  return 0;
	case '<':
	  depth++;		/* start nested template */
	  if (just_seen_colon || just_seen_right || just_seen_space)
	    return 0;		/* but not after : or :: or > or space */
	  break;
	case '>':
	  if (just_seen_colon || just_seen_right)
	    return 0;		/* end a (nested?) template */
	  just_seen_right = 1;	/* but not after : or :: */
	  if (--depth == 0)	/* also disallow >>, insist on > > */
	    return ++p;		/* if outermost ended, return */
	  break;
	case ':':
	  if (just_seen_space || (just_seen_colon > 1))
	    return 0;		/* nested class spec coming up */
	  just_seen_colon++;	/* we allow :: but not :::: */
	  break;
	case ' ':
	  break;
	default:
	  if (!((*p >= 'a' && *p <= 'z') ||	/* allow token chars */
		(*p >= 'A' && *p <= 'Z') ||
		(*p >= '0' && *p <= '9') ||
		(*p == '_') || (*p == ',') ||	/* commas for template args */
		(*p == '&') || (*p == '*') ||	/* pointer and ref types */
		(*p == '(') || (*p == ')') ||	/* function types */
		(*p == '[') || (*p == ']')))	/* array types */
	    return 0;
	}
      if (*p != ' ')
	just_seen_space = 0;
      if (*p != ':')
	just_seen_colon = 0;
      if (*p != '>')
	just_seen_right = 0;
    }
  return 0;
}