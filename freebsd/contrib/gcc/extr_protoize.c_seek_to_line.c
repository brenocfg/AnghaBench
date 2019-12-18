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
 int /*<<< orphan*/  check_source (int,int /*<<< orphan*/ ) ; 
 char* clean_text_limit ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int last_known_line_number ; 
 char* last_known_line_start ; 

__attribute__((used)) static const char *
seek_to_line (int n)
{
  gcc_assert (n >= last_known_line_number);

  while (n > last_known_line_number)
    {
      while (*last_known_line_start != '\n')
	check_source (++last_known_line_start < clean_text_limit, 0);
      last_known_line_start++;
      last_known_line_number++;
    }
  return last_known_line_start;
}