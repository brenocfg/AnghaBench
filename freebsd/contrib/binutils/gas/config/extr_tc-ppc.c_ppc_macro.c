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
struct powerpc_macro {unsigned int operands; char* format; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ alloca (unsigned int) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/  md_assemble (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 unsigned int strtol (char const*,char**,int) ; 

__attribute__((used)) static void
ppc_macro (char *str, const struct powerpc_macro *macro)
{
  char *operands[10];
  unsigned int count;
  char *s;
  unsigned int len;
  const char *format;
  unsigned int arg;
  char *send;
  char *complete;

  /* Gather the users operands into the operands array.  */
  count = 0;
  s = str;
  while (1)
    {
      if (count >= sizeof operands / sizeof operands[0])
	break;
      operands[count++] = s;
      s = strchr (s, ',');
      if (s == (char *) NULL)
	break;
      *s++ = '\0';
    }

  if (count != macro->operands)
    {
      as_bad (_("wrong number of operands"));
      return;
    }

  /* Work out how large the string must be (the size is unbounded
     because it includes user input).  */
  len = 0;
  format = macro->format;
  while (*format != '\0')
    {
      if (*format != '%')
	{
	  ++len;
	  ++format;
	}
      else
	{
	  arg = strtol (format + 1, &send, 10);
	  know (send != format && arg < count);
	  len += strlen (operands[arg]);
	  format = send;
	}
    }

  /* Put the string together.  */
  complete = s = (char *) alloca (len + 1);
  format = macro->format;
  while (*format != '\0')
    {
      if (*format != '%')
	*s++ = *format++;
      else
	{
	  arg = strtol (format + 1, &send, 10);
	  strcpy (s, operands[arg]);
	  s += strlen (s);
	  format = send;
	}
    }
  *s = '\0';

  /* Assemble the constructed instruction.  */
  md_assemble (complete);
}