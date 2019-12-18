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
typedef  int /*<<< orphan*/  symbolS ;
struct expr_symbol_line {char* file; unsigned int line; int /*<<< orphan*/ * sym; struct expr_symbol_line* next; } ;

/* Variables and functions */
 struct expr_symbol_line* expr_symbol_lines ; 

int
expr_symbol_where (symbolS *sym, char **pfile, unsigned int *pline)
{
  register struct expr_symbol_line *l;

  for (l = expr_symbol_lines; l != NULL; l = l->next)
    {
      if (l->sym == sym)
	{
	  *pfile = l->file;
	  *pline = l->line;
	  return 1;
	}
    }

  return 0;
}