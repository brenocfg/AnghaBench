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
 int /*<<< orphan*/  SB_append_char (int /*<<< orphan*/ ,int) ; 
 int* SB_contents (int /*<<< orphan*/ ) ; 
 int SB_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_set_length (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  conf_linenum ; 
 int conf_next_low () ; 
 int /*<<< orphan*/  current_linenum ; 
 scalar_t__ is_ws (int) ; 
 int /*<<< orphan*/  line_builder ; 

__attribute__((used)) static int
conf_next_line(void)
{
	for (;;) {
		int c;
		int lcwb;

		SB_reset(line_builder);

		/*
		 * Get first non-whitespace character. This skips empty
		 * lines. Comment lines (first non-whitespace character
		 * is a semicolon) are also skipped.
		 */
		for (;;) {
			c = conf_next_low();
			if (c < 0) {
				return -1;
			}
			if (is_ws(c)) {
				continue;
			}
			if (c == ';') {
				for (;;) {
					c = conf_next_low();
					if (c < 0) {
						return -1;
					}
					if (c == '\n') {
						break;
					}
				}
				continue;
			}
			break;
		}

		/*
		 * Read up the remaining of the line. The line continuation
		 * sequence (final backslash) is detected and processed.
		 */
		current_linenum = conf_linenum;
		lcwb = (c == '\\');
		SB_append_char(line_builder, c);
		for (;;) {
			c = conf_next_low();
			if (c < 0) {
				break;
			}
			if (lcwb) {
				if (c == '\n') {
					SB_set_length(line_builder,
						SB_length(line_builder) - 1);
				}
				lcwb = 0;
				continue;
			}
			if (c == '\n') {
				break;
			} else if (c == '\\') {
				lcwb = 1;
			}
			SB_append_char(line_builder, c);
		}

		/*
		 * Remove trailing whitespace (if any).
		 */
		for (;;) {
			size_t u;

			u = SB_length(line_builder);
			if (u == 0 || !is_ws(
				SB_contents(line_builder)[u - 1]))
			{
				break;
			}
			SB_set_length(line_builder, u - 1);
		}

		/*
		 * We might end up with a totally empty line (in case there
		 * was a line continuation but nothing else), in which case
		 * we must loop.
		 */
		if (SB_length(line_builder) > 0) {
			return 0;
		}
	}
}