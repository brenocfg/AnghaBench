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
 int /*<<< orphan*/  c_override_global_bindings_to_false ; 
 scalar_t__ current_scope ; 
 scalar_t__ file_scope ; 

int
global_bindings_p (void)
{
  return current_scope == file_scope && !c_override_global_bindings_to_false;
}