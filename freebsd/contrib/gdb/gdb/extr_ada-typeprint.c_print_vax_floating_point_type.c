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
 int /*<<< orphan*/  ada_vax_float_type_suffix (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_vax_floating_point_type (struct type *type, struct ui_file *stream)
{
  fprintf_filtered (stream, "<float format %c>",
		    ada_vax_float_type_suffix (type));
}