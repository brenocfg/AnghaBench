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
 int lv1_send_event_locally (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virq_to_hw (unsigned int) ; 

int ps3_send_event_locally(unsigned int virq)
{
	return lv1_send_event_locally(virq_to_hw(virq));
}