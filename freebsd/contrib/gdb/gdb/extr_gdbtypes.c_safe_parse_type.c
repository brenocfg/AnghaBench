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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 struct type* builtin_type_void ; 
 int /*<<< orphan*/  gdb_parse_and_eval_type (char*,int,struct type**) ; 
 struct ui_file* gdb_stderr ; 
 int /*<<< orphan*/  ui_file_delete (struct ui_file*) ; 
 struct ui_file* ui_file_new () ; 

__attribute__((used)) static struct type *
safe_parse_type (char *p, int length)
{
  struct ui_file *saved_gdb_stderr;
  struct type *type;

  /* Suppress error messages. */
  saved_gdb_stderr = gdb_stderr;
  gdb_stderr = ui_file_new ();

  /* Call parse_and_eval_type() without fear of longjmp()s. */
  if (!gdb_parse_and_eval_type (p, length, &type))
    type = builtin_type_void;

  /* Stop suppressing error messages. */
  ui_file_delete (gdb_stderr);
  gdb_stderr = saved_gdb_stderr;

  return type;
}