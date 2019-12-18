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
struct d_print_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_DIGIT (char const) ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char const) ; 

__attribute__((used)) static void
d_print_java_identifier (struct d_print_info *dpi, const char *name, int len)
{
  const char *p;
  const char *end;

  end = name + len;
  for (p = name; p < end; ++p)
    {
      if (end - p > 3
	  && p[0] == '_'
	  && p[1] == '_'
	  && p[2] == 'U')
	{
	  unsigned long c;
	  const char *q;

	  c = 0;
	  for (q = p + 3; q < end; ++q)
	    {
	      int dig;

	      if (IS_DIGIT (*q))
		dig = *q - '0';
	      else if (*q >= 'A' && *q <= 'F')
		dig = *q - 'A' + 10;
	      else if (*q >= 'a' && *q <= 'f')
		dig = *q - 'a' + 10;
	      else
		break;

	      c = c * 16 + dig;
	    }
	  /* If the Unicode character is larger than 256, we don't try
	     to deal with it here.  FIXME.  */
	  if (q < end && *q == '_' && c < 256)
	    {
	      d_append_char (dpi, c);
	      p = q;
	      continue;
	    }
	}

      d_append_char (dpi, *p);
    }
}