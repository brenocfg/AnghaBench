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
typedef  int /*<<< orphan*/  bondport_ref ;

/* Variables and functions */
 int /*<<< orphan*/  SelectedState_UNSELECTED ; 
 int /*<<< orphan*/  bondport_set_selected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_UpdateDefaultSelected(bondport_ref p)
{
    bondport_set_selected(p, SelectedState_UNSELECTED);
    return;
}