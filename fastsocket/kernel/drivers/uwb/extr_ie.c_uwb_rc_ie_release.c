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
struct uwb_rc {scalar_t__ ies_capacity; int /*<<< orphan*/ * ies; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void uwb_rc_ie_release(struct uwb_rc *uwb_rc)
{
	kfree(uwb_rc->ies);
	uwb_rc->ies = NULL;
	uwb_rc->ies_capacity = 0;
}