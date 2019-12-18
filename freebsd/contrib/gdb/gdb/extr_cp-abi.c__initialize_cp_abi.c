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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auto_cp_abi ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  register_cp_abi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cp_abi_cmd ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  show_cp_abi_cmd ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  switch_to_cp_abi (char*) ; 

void
_initialize_cp_abi (void)
{
  register_cp_abi (&auto_cp_abi);
  switch_to_cp_abi ("auto");

  add_cmd ("cp-abi", class_obscure, set_cp_abi_cmd,
	   "Set the ABI used for inspecting C++ objects.\n"
	   "\"set cp-abi\" with no arguments will list the available ABIs.",
	   &setlist);

  add_cmd ("cp-abi", class_obscure, show_cp_abi_cmd,
	   "Show the ABI used for inspecting C++ objects.", &showlist);
}