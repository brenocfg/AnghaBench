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
struct value {int dummy; } ;
struct ui_file {int dummy; } ;
struct symbol {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Val_pretty_default ; 
 struct value* read_var_value (struct symbol*,struct frame_info*) ; 
 int /*<<< orphan*/  value_print (struct value*,struct ui_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
print_variable_value (struct symbol *var, struct frame_info *frame,
		      struct ui_file *stream)
{
  struct value *val = read_var_value (var, frame);

  value_print (val, stream, 0, Val_pretty_default);
}