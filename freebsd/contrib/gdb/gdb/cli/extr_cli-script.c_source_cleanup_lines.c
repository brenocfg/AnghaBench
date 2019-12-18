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
struct source_cleanup_lines_args {int /*<<< orphan*/  old_error_pre_print; int /*<<< orphan*/  old_pre_error; int /*<<< orphan*/  old_file; int /*<<< orphan*/  old_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  error_pre_print ; 
 int /*<<< orphan*/  source_file_name ; 
 int /*<<< orphan*/  source_line_number ; 
 int /*<<< orphan*/  source_pre_error ; 

__attribute__((used)) static void
source_cleanup_lines (void *args)
{
  struct source_cleanup_lines_args *p =
  (struct source_cleanup_lines_args *) args;
  source_line_number = p->old_line;
  source_file_name = p->old_file;
  source_pre_error = p->old_pre_error;
  error_pre_print = p->old_error_pre_print;
}