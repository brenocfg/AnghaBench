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
struct coff_line {int nlines; int* lines; int* addresses; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  tab (int) ; 

__attribute__((used)) static void
dump_coff_lines (struct coff_line *p)
{
  int i;
  int online = 0;

  tab (1);
  printf (_("#lines %d "),p->nlines);

  for (i = 0; i < p->nlines; i++)
    {
      printf ("(%d 0x%x)", p->lines[i], p->addresses[i]);

      online++;

      if (online > 6)
	{
	  nl ();
	  tab (0);
	  online = 0;
	}
    }
  nl ();
  tab (-1);
}