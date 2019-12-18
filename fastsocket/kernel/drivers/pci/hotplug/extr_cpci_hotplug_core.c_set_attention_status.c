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
typedef  int /*<<< orphan*/  u8 ;
struct hotplug_slot {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int cpci_set_attention_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_attention_status(struct hotplug_slot *hotplug_slot, u8 status)
{
	return cpci_set_attention_status(hotplug_slot->private, status);
}