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
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  connect_command ; 
 int /*<<< orphan*/  init_st2000_ops () ; 
 int /*<<< orphan*/  st2000_command ; 
 int /*<<< orphan*/  st2000_ops ; 

void
_initialize_remote_st2000 (void)
{
  init_st2000_ops ();
  add_target (&st2000_ops);
  add_com ("st2000 <command>", class_obscure, st2000_command,
	   "Send a command to the STDBUG monitor.");
  add_com ("connect", class_obscure, connect_command,
	   "Connect the terminal directly up to the STDBUG command monitor.\n\
Use <CR>~. or <CR>~^D to break out.");
}