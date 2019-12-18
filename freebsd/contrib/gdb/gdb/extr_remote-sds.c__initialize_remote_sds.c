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
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  init_sds_ops () ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  sds_command ; 
 int /*<<< orphan*/  sds_ops ; 
 int /*<<< orphan*/  sds_timeout ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_integer ; 

void
_initialize_remote_sds (void)
{
  init_sds_ops ();
  add_target (&sds_ops);

  add_show_from_set (add_set_cmd ("sdstimeout", no_class,
				  var_integer, (char *) &sds_timeout,
			     "Set timeout value for sds read.\n", &setlist),
		     &showlist);

  add_com ("sds", class_obscure, sds_command,
	   "Send a command to the SDS monitor.");
}