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
 scalar_t__ ENABLE_SCOPE_CHECKING ; 
 int /*<<< orphan*/  begin_scope (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_binding_level ; 
 int /*<<< orphan*/  current_class_type ; 
 int is_class_level ; 
 int /*<<< orphan*/  sk_class ; 

void
pushlevel_class (void)
{
  if (ENABLE_SCOPE_CHECKING)
    is_class_level = 1;

  class_binding_level = begin_scope (sk_class, current_class_type);
}