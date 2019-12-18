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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kod_set_os ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  operating_system ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_string ; 

void
_initialize_kod (void)
{
  struct cmd_list_element *c;

  c = add_set_cmd ("os", no_class, var_string,
		   (char *) &operating_system,
		   "Set operating system",
		   &setlist);
  set_cmd_sfunc (c, kod_set_os);
  add_show_from_set (c, &showlist);
}