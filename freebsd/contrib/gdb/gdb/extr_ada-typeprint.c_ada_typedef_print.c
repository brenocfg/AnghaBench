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
struct symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_PRINT_NAME (struct symbol*) ; 
 int /*<<< orphan*/  ada_name_prefix_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,struct ui_file*,int) ; 

void
ada_typedef_print (struct type *type, struct symbol *new,
		   struct ui_file *stream)
{
  fprintf_filtered (stream, "type %.*s is ",
		    ada_name_prefix_len (SYMBOL_PRINT_NAME (new)),
		    SYMBOL_PRINT_NAME (new));
  type_print (type, "", stream, 1);
}