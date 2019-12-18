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
 char* buffer_limit ; 
 int /*<<< orphan*/  bump_line_counters () ; 
 char* find_end_of_line (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_m68k_mri ; 
 char* input_line_pointer ; 
 char* input_scrub_next_buffer (char**) ; 
 int /*<<< orphan*/  sb_add_buffer (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
get_line_sb (sb *line)
{
  char *eol;

  if (input_line_pointer[-1] == '\n')
    bump_line_counters ();

  if (input_line_pointer >= buffer_limit)
    {
      buffer_limit = input_scrub_next_buffer (&input_line_pointer);
      if (buffer_limit == 0)
	return 0;
    }

  eol = find_end_of_line (input_line_pointer, flag_m68k_mri);
  sb_add_buffer (line, input_line_pointer, eol - input_line_pointer);
  input_line_pointer = eol;

  /* Don't skip multiple end-of-line characters, because that breaks support
     for the IA-64 stop bit (;;) which looks like two consecutive end-of-line
     characters but isn't.  Instead just skip one end of line character and
     return the character skipped so that the caller can re-insert it if
     necessary.   */
  return *input_line_pointer++;
}