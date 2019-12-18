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
 int /*<<< orphan*/  case_sensitive ; 
 scalar_t__ current_language ; 
 scalar_t__ expected_language ; 
 int /*<<< orphan*/  language ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range ; 
 int /*<<< orphan*/  show_case_command (char*,int) ; 
 int /*<<< orphan*/  show_language_command (char*,int) ; 
 int /*<<< orphan*/  show_range_command (char*,int) ; 
 int /*<<< orphan*/  show_type_command (char*,int) ; 
 int /*<<< orphan*/  type ; 

void
language_info (int quietly)
{
  if (quietly && expected_language == current_language)
    return;

  expected_language = current_language;
  printf_unfiltered ("Current language:  %s\n", language);
  show_language_command ((char *) 0, 1);

  if (!quietly)
    {
      printf_unfiltered ("Type checking:     %s\n", type);
      show_type_command ((char *) 0, 1);
      printf_unfiltered ("Range checking:    %s\n", range);
      show_range_command ((char *) 0, 1);
      printf_unfiltered ("Case sensitivity:  %s\n", case_sensitive);
      show_case_command ((char *) 0, 1);
    }
}