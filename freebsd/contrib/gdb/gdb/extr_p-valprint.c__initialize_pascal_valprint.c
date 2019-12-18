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
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_support ; 
 int pascal_static_field_print ; 
 int /*<<< orphan*/  setprintlist ; 
 int /*<<< orphan*/  showprintlist ; 
 int /*<<< orphan*/  var_boolean ; 

void
_initialize_pascal_valprint (void)
{
  add_show_from_set
    (add_set_cmd ("pascal_static-members", class_support, var_boolean,
		  (char *) &pascal_static_field_print,
		  "Set printing of pascal static members.",
		  &setprintlist),
     &showprintlist);
  /* Turn on printing of static fields.  */
  pascal_static_field_print = 1;

}