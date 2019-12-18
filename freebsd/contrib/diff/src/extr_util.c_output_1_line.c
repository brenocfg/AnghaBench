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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  expand_tabs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  putc (unsigned char,int /*<<< orphan*/ *) ; 
 size_t tabsize ; 

void
output_1_line (char const *base, char const *limit, char const *flag_format,
	       char const *line_flag)
{
  if (!expand_tabs)
    fwrite (base, sizeof (char), limit - base, outfile);
  else
    {
      register FILE *out = outfile;
      register unsigned char c;
      register char const *t = base;
      register size_t column = 0;
      size_t tab_size = tabsize;

      while (t < limit)
	switch ((c = *t++))
	  {
	  case '\t':
	    {
	      size_t spaces = tab_size - column % tab_size;
	      column += spaces;
	      do
		putc (' ', out);
	      while (--spaces);
	    }
	    break;

	  case '\r':
	    putc (c, out);
	    if (flag_format && t < limit && *t != '\n')
	      fprintf (out, flag_format, line_flag);
	    column = 0;
	    break;

	  case '\b':
	    if (column == 0)
	      continue;
	    column--;
	    putc (c, out);
	    break;

	  default:
	    column += isprint (c) != 0;
	    putc (c, out);
	    break;
	  }
    }
}