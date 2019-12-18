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
struct line_map {int sysp; scalar_t__ to_file; } ;
typedef  int /*<<< orphan*/  source_location ;
struct TYPE_2__ {int src_line; int /*<<< orphan*/  outf; scalar_t__ printed; } ;

/* Variables and functions */
 int SOURCE_LINE (struct line_map const*,int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (size_t) ; 
 unsigned char* cpp_quote_string (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  flag_no_line_commands ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_table ; 
 struct line_map* linemap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ print ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 size_t strlen (scalar_t__) ; 

__attribute__((used)) static void
print_line (source_location src_loc, const char *special_flags)
{
  /* End any previous line of text.  */
  if (print.printed)
    putc ('\n', print.outf);
  print.printed = 0;

  if (!flag_no_line_commands)
    {
      const struct line_map *map = linemap_lookup (&line_table, src_loc);

      size_t to_file_len = strlen (map->to_file);
      unsigned char *to_file_quoted =
         (unsigned char *) alloca (to_file_len * 4 + 1);
      unsigned char *p;

      print.src_line = SOURCE_LINE (map, src_loc);

      /* cpp_quote_string does not nul-terminate, so we have to do it
	 ourselves.  */
      p = cpp_quote_string (to_file_quoted,
			    (unsigned char *) map->to_file, to_file_len);
      *p = '\0';
      fprintf (print.outf, "# %u \"%s\"%s",
	       print.src_line == 0 ? 1 : print.src_line,
	       to_file_quoted, special_flags);

      if (map->sysp == 2)
	fputs (" 3 4", print.outf);
      else if (map->sysp == 1)
	fputs (" 3", print.outf);

      putc ('\n', print.outf);
    }
}