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
 char at (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  catchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  cattext (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  delete_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_string (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/ * tos ; 

__attribute__((used)) static void
bulletize ()
{
  unsigned int idx = 0;
  int on = 0;
  string_type out;
  init_string (&out);

  while (at (tos, idx))
    {
      if (at (tos, idx) == '@'
	  && at (tos, idx + 1) == '*')
	{
	  cattext (&out, "*");
	  idx += 2;
	}
      else if (at (tos, idx) == '\n'
	       && at (tos, idx + 1) == 'o'
	       && isspace ((unsigned char) at (tos, idx + 2)))
	{
	  if (!on)
	    {
	      cattext (&out, "\n@itemize @bullet\n");
	      on = 1;

	    }
	  cattext (&out, "\n@item\n");
	  idx += 3;
	}
      else
	{
	  catchar (&out, at (tos, idx));
	  if (on && at (tos, idx) == '\n'
	      && at (tos, idx + 1) == '\n'
	      && at (tos, idx + 2) != 'o')
	    {
	      cattext (&out, "@end itemize");
	      on = 0;
	    }
	  idx++;

	}
    }
  if (on)
    {
      cattext (&out, "@end itemize\n");
    }

  delete_string (tos);
  *tos = out;
  pc++;
}