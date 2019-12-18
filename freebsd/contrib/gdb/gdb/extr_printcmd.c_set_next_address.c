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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  builtin_type_void ; 
 int /*<<< orphan*/  lookup_internalvar (char*) ; 
 int /*<<< orphan*/  lookup_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_address ; 
 int /*<<< orphan*/  set_internalvar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_from_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
set_next_address (CORE_ADDR addr)
{
  next_address = addr;

  /* Make address available to the user as $_.  */
  set_internalvar (lookup_internalvar ("_"),
		   value_from_pointer (lookup_pointer_type (builtin_type_void),
				       addr));
}