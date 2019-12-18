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
struct deps {unsigned int ntargets; char** targetv; unsigned int ndeps; char** depv; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 unsigned int strlen (char*) ; 

void
deps_write (const struct deps *d, FILE *fp, unsigned int colmax)
{
  unsigned int size, i, column;

  column = 0;
  if (colmax && colmax < 34)
    colmax = 34;

  for (i = 0; i < d->ntargets; i++)
    {
      size = strlen (d->targetv[i]);
      column += size;
      if (colmax && column > colmax)
	{
	  fputs (" \\\n ", fp);
	  column = 1 + size;
	}
      if (i)
	{
	  putc (' ', fp);
	  column++;
	}
      fputs (d->targetv[i], fp);
    }

  putc (':', fp);
  putc (' ', fp);
  column += 2;

  for (i = 0; i < d->ndeps; i++)
    {
      size = strlen (d->depv[i]);
      column += size;
      if (colmax && column > colmax)
	{
	  fputs (" \\\n ", fp);
	  column = 1 + size;
	}
      if (i)
	{
	  putc (' ', fp);
	  column++;
	}
      fputs (d->depv[i], fp);
    }
  putc ('\n', fp);
}