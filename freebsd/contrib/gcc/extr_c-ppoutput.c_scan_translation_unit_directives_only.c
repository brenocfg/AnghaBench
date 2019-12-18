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
struct _cpp_dir_only_callbacks {int /*<<< orphan*/  maybe_print_line; int /*<<< orphan*/  print_lines; } ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  _cpp_preprocess_dir_only (int /*<<< orphan*/ *,struct _cpp_dir_only_callbacks*) ; 
 int /*<<< orphan*/  maybe_print_line ; 
 int /*<<< orphan*/  print_lines_directives_only ; 

__attribute__((used)) static void
scan_translation_unit_directives_only (cpp_reader *pfile)
{
  struct _cpp_dir_only_callbacks cb;

  cb.print_lines = print_lines_directives_only;
  cb.maybe_print_line = maybe_print_line;

  _cpp_preprocess_dir_only (pfile, &cb);
}