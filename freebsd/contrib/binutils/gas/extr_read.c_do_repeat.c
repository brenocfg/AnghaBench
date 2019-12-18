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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  buffer_and_nest (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_limit ; 
 int /*<<< orphan*/  get_line_sb ; 
 int /*<<< orphan*/  input_line_pointer ; 
 int /*<<< orphan*/  input_scrub_include_sb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_scrub_next_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_add_sb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_new (int /*<<< orphan*/ *) ; 

void
do_repeat (int count, const char *start, const char *end)
{
  sb one;
  sb many;

  sb_new (&one);
  if (!buffer_and_nest (start, end, &one, get_line_sb))
    {
      as_bad (_("%s without %s"), start, end);
      return;
    }

  sb_new (&many);
  while (count-- > 0)
    sb_add_sb (&many, &one);

  sb_kill (&one);

  input_scrub_include_sb (&many, input_line_pointer, 1);
  sb_kill (&many);
  buffer_limit = input_scrub_next_buffer (&input_line_pointer);
}