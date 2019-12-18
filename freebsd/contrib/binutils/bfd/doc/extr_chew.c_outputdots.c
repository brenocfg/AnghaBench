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
 int /*<<< orphan*/  overwrite_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/  tos ; 

__attribute__((used)) static void
outputdots ()
{
  unsigned int idx = 0;
  string_type out;
  init_string (&out);

  while (at (tos, idx))
    {
      if (at (tos, idx) == '\n' && at (tos, idx + 1) == '.')
	{
	  char c;
	  idx += 2;

	  while ((c = at (tos, idx)) && c != '\n')
	    {
	      if (c == '{' && at (tos, idx + 1) == '*')
		{
		  cattext (&out, "/*");
		  idx += 2;
		}
	      else if (c == '*' && at (tos, idx + 1) == '}')
		{
		  cattext (&out, "*/");
		  idx += 2;
		}
	      else
		{
		  catchar (&out, c);
		  idx++;
		}
	    }
	  catchar (&out, '\n');
	}
      else
	{
	  idx++;
	}
    }

  overwrite_string (tos, &out);
  pc++;
}