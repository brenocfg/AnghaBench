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
typedef  int /*<<< orphan*/  sb ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_limit ; 
 int /*<<< orphan*/  input_line_pointer ; 
 int /*<<< orphan*/  input_scrub_include_sb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_scrub_next_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_add_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  sb_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_new (int /*<<< orphan*/ *) ; 

void
input_scrub_insert_line (const char *line)
{
  sb newline;
  sb_new (&newline);
  sb_add_string (&newline, line);
  input_scrub_include_sb (&newline, input_line_pointer, 0);
  sb_kill (&newline);
  buffer_limit = input_scrub_next_buffer (&input_line_pointer);
}