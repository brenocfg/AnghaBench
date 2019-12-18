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
 int /*<<< orphan*/  c_register_pragma (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_pragma_implementation ; 
 int /*<<< orphan*/  handle_pragma_interface ; 
 int /*<<< orphan*/  handle_pragma_java_exceptions ; 
 int /*<<< orphan*/  handle_pragma_unit ; 
 int /*<<< orphan*/  handle_pragma_vtable ; 

__attribute__((used)) static void
init_cp_pragma (void)
{
  c_register_pragma (0, "vtable", handle_pragma_vtable);
  c_register_pragma (0, "unit", handle_pragma_unit);
  c_register_pragma (0, "interface", handle_pragma_interface);
  c_register_pragma (0, "implementation", handle_pragma_implementation);
  c_register_pragma ("GCC", "interface", handle_pragma_interface);
  c_register_pragma ("GCC", "implementation", handle_pragma_implementation);
  c_register_pragma ("GCC", "java_exceptions", handle_pragma_java_exceptions);
}