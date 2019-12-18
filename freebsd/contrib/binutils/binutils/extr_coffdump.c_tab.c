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
 scalar_t__ atnl ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
tab (int x)
{
  static int indent;
  int i;

  if (atnl)
    {
      if (x < 0)
	{
	  printf (")");
	  indent += x;

	  return;
	}
      else
	{
	  printf ("\n");
	  atnl = 0;
	}
    }

  if (x == -1)
    {
      for (i = 0; i < indent; i++)
	printf ("   ");

      indent += x;
      printf (")");
      return;
    }

  indent += x;

  for (i = 0; i < indent; i++)
    printf ("   ");

  if (x)
    {
      printf ("(");
    }
}