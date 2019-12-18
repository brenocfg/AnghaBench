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
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  list_cp_abis (int) ; 
 int /*<<< orphan*/  switch_to_cp_abi (char*) ; 

__attribute__((used)) static void
set_cp_abi_cmd (char *args, int from_tty)
{
  if (args == NULL)
    {
      list_cp_abis (from_tty);
      return;
    }

  if (!switch_to_cp_abi (args))
    error ("Could not find \"%s\" in ABI list", args);
}