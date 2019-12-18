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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 scalar_t__ ISBLANK (char const) ; 
 int /*<<< orphan*/  pp_append_text (int /*<<< orphan*/ *,char const*,char const*) ; 
 int pp_is_wrapping_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_newline (int /*<<< orphan*/ *) ; 
 int pp_remaining_character_count_for_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_wrap_text (pretty_printer *pp, const char *start, const char *end)
{
  bool wrapping_line = pp_is_wrapping_line (pp);

  while (start != end)
    {
      /* Dump anything bordered by whitespaces.  */
      {
	const char *p = start;
	while (p != end && !ISBLANK (*p) && *p != '\n')
	  ++p;
	if (wrapping_line
            && p - start >= pp_remaining_character_count_for_line (pp))
	  pp_newline (pp);
	pp_append_text (pp, start, p);
	start = p;
      }

      if (start != end && ISBLANK (*start))
	{
	  pp_space (pp);
	  ++start;
	}
      if (start != end && *start == '\n')
	{
	  pp_newline (pp);
	  ++start;
	}
    }
}