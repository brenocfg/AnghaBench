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
 int at (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  catchar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cattext (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  delete_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc ; 
 int /*<<< orphan*/ * tos ; 

__attribute__((used)) static void
indent ()
{
  string_type out;
  int tab = 0;
  int idx = 0;
  int ol = 0;
  init_string (&out);
  while (at (tos, idx))
    {
      switch (at (tos, idx))
	{
	case '\n':
	  cattext (&out, "\n");
	  idx++;
	  if (tab && at (tos, idx))
	    {
	      cattext (&out, "    ");
	    }
	  ol = 0;
	  break;
	case '(':
	  tab++;
	  if (ol == 0)
	    cattext (&out, "   ");
	  idx++;
	  cattext (&out, "(");
	  ol = 1;
	  break;
	case ')':
	  tab--;
	  cattext (&out, ")");
	  idx++;
	  ol = 1;

	  break;
	default:
	  catchar (&out, at (tos, idx));
	  ol = 1;

	  idx++;
	  break;
	}
    }

  pc++;
  delete_string (tos);
  *tos = out;

}