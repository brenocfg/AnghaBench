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
typedef  int /*<<< orphan*/  string_type ;

/* Variables and functions */
 char at (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  catchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  cattext (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_string (int /*<<< orphan*/ *) ; 
 scalar_t__ islower (unsigned char) ; 
 int /*<<< orphan*/  overwrite_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/  tos ; 

__attribute__((used)) static void
courierize ()
{
  string_type out;
  unsigned int idx = 0;
  int command = 0;

  init_string (&out);

  while (at (tos, idx))
    {
      if (at (tos, idx) == '\n'
	  && (at (tos, idx +1 ) == '.'
	      || at (tos, idx + 1) == '|'))
	{
	  cattext (&out, "\n@example\n");
	  do
	    {
	      idx += 2;

	      while (at (tos, idx) && at (tos, idx) != '\n')
		{
		  if (command > 1)
		    {
		      /* We are inside {} parameters of some command;
			 Just pass through until matching brace.  */
		      if (at (tos, idx) == '{')
			++command;
		      else if (at (tos, idx) == '}')
			--command;
		    }
		  else if (command != 0)
		    {
		      if (at (tos, idx) == '{')
			++command;
		      else if (!islower ((unsigned char) at (tos, idx)))
			--command;
		    }
		  else if (at (tos, idx) == '@'
			   && islower ((unsigned char) at (tos, idx + 1)))
		    {
		      ++command;
		    }
		  else if (at (tos, idx) == '{' && at (tos, idx + 1) == '*')
		    {
		      cattext (&out, "/*");
		      idx += 2;
		      continue;
		    }
		  else if (at (tos, idx) == '*' && at (tos, idx + 1) == '}')
		    {
		      cattext (&out, "*/");
		      idx += 2;
		      continue;
		    }
		  else if (at (tos, idx) == '{'
			   || at (tos, idx) == '}')
		    {
		      catchar (&out, '@');
		    }

		  catchar (&out, at (tos, idx));
		  idx++;
		}
	      catchar (&out, '\n');
	    }
	  while (at (tos, idx) == '\n'
		 && ((at (tos, idx + 1) == '.')
		     || (at (tos, idx + 1) == '|')))
	    ;
	  cattext (&out, "@end example");
	}
      else
	{
	  catchar (&out, at (tos, idx));
	  idx++;
	}
    }

  overwrite_string (tos, &out);
  pc++;
}