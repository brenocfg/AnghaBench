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
 int /*<<< orphan*/  as_bad_where (char*,unsigned int,char*,char const*) ; 
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 int /*<<< orphan*/  buffer_limit ; 
 char* expand_irp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* find_end_of_line (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_line_sb ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  input_scrub_include_sb (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_scrub_next_buffer (char**) ; 
 int /*<<< orphan*/  sb_add_buffer (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sb_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_new (int /*<<< orphan*/ *) ; 

void
s_irp (int irpc)
{
  char *file, *eol;
  unsigned int line;
  sb s;
  const char *err;
  sb out;

  as_where (&file, &line);

  sb_new (&s);
  eol = find_end_of_line (input_line_pointer, 0);
  sb_add_buffer (&s, input_line_pointer, eol - input_line_pointer);
  input_line_pointer = eol;

  sb_new (&out);

  err = expand_irp (irpc, 0, &s, &out, get_line_sb);
  if (err != NULL)
    as_bad_where (file, line, "%s", err);

  sb_kill (&s);

  input_scrub_include_sb (&out, input_line_pointer, 1);
  sb_kill (&out);
  buffer_limit = input_scrub_next_buffer (&input_line_pointer);
}