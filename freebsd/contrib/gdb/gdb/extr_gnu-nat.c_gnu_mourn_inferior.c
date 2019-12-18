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
 int /*<<< orphan*/  current_inferior ; 
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  gnu_ops ; 
 int /*<<< orphan*/  inf_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  inf_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gnu_mourn_inferior (void)
{
  inf_debug (current_inferior, "rip");
  inf_detach (current_inferior);
  unpush_target (&gnu_ops);
  generic_mourn_inferior ();
}