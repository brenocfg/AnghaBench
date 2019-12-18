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
struct slot {int dummy; } ;
struct hotplug_slot {struct slot* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpci_get_attention_status (struct slot*) ; 

__attribute__((used)) static int
get_attention_status(struct hotplug_slot *hotplug_slot, u8 * value)
{
	struct slot *slot = hotplug_slot->private;

	*value = cpci_get_attention_status(slot);
	return 0;
}