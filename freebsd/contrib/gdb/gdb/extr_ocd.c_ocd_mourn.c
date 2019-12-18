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
 int /*<<< orphan*/  current_ops ; 
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ ) ; 

void
ocd_mourn (void)
{
  unpush_target (current_ops);
  generic_mourn_inferior ();
}