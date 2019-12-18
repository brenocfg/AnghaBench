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
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 size_t tabsize ; 

__attribute__((used)) static size_t
tab_from_to (size_t from, size_t to)
{
  FILE *out = outfile;
  size_t tab;
  size_t tab_size = tabsize;

  if (!expand_tabs)
    for (tab = from + tab_size - from % tab_size;  tab <= to;  tab += tab_size)
      {
	putc ('\t', out);
	from = tab;
      }
  while (from++ < to)
    putc (' ', out);
  return to;
}