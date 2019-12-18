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
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/ * tos ; 

__attribute__((used)) static void
do_fancy_stuff ()
{
  unsigned int idx = 0;
  string_type out;
  init_string (&out);
  while (at (tos, idx))
    {
      if (at (tos, idx) == '<'
	  && at (tos, idx + 1) == '<'
	  && !isspace ((unsigned char) at (tos, idx + 2)))
	{
	  /* This qualifies as a << startup.  */
	  idx += 2;
	  cattext (&out, "@code{");
	  while (at (tos, idx)
		 && at (tos, idx) != '>' )
	    {
	      catchar (&out, at (tos, idx));
	      idx++;

	    }
	  cattext (&out, "}");
	  idx += 2;
	}
      else
	{
	  catchar (&out, at (tos, idx));
	  idx++;
	}
    }
  delete_string (tos);
  *tos = out;
  pc++;

}