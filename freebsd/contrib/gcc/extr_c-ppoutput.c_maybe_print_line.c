#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct line_map {int dummy; } ;
typedef  int /*<<< orphan*/  source_location ;
struct TYPE_2__ {int src_line; int /*<<< orphan*/  outf; scalar_t__ printed; } ;

/* Variables and functions */
 int SOURCE_LINE (struct line_map const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_table ; 
 struct line_map* linemap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ print ; 
 int /*<<< orphan*/  print_line (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maybe_print_line (source_location src_loc)
{
  const struct line_map *map = linemap_lookup (&line_table, src_loc);
  int src_line = SOURCE_LINE (map, src_loc);
  /* End the previous line of text.  */
  if (print.printed)
    {
      putc ('\n', print.outf);
      print.src_line++;
      print.printed = 0;
    }

  if (src_line >= print.src_line && src_line < print.src_line + 8)
    {
      while (src_line > print.src_line)
	{
	  putc ('\n', print.outf);
	  print.src_line++;
	}
    }
  else
    print_line (src_loc, "");
}