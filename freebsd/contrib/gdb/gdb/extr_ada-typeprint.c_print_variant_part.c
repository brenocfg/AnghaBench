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
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/  ada_variant_discrim_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,int,char*,...) ; 
 int /*<<< orphan*/  print_variant_clauses (struct type*,int,struct type*,struct ui_file*,int,int) ; 

__attribute__((used)) static void
print_variant_part (struct type *type, int field_num, struct type *outer_type,
		    struct ui_file *stream, int show, int level)
{
  fprintf_filtered (stream, "\n%*scase %s is", level + 4, "",
		    ada_variant_discrim_name
		    (TYPE_FIELD_TYPE (type, field_num)));
  print_variant_clauses (type, field_num, outer_type, stream, show,
			 level + 4);
  fprintf_filtered (stream, "\n%*send case;", level + 4, "");
}