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
 int /*<<< orphan*/  convert_filename ; 
 int /*<<< orphan*/  identify_lineno (char const*) ; 
 int /*<<< orphan*/  last_known_line_number ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quiet_flag ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  source_confusion_recovery ; 

__attribute__((used)) static void
declare_source_confusing (const char *clean_p)
{
  if (!quiet_flag)
    {
      if (clean_p == 0)
	notice ("%s: %d: warning: source too confusing\n",
		shortpath (NULL, convert_filename), last_known_line_number);
      else
	notice ("%s: %d: warning: source too confusing\n",
		shortpath (NULL, convert_filename),
		identify_lineno (clean_p));
    }
  longjmp (source_confusion_recovery, 1);
}