#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ prev; } ;
struct TYPE_4__ {TYPE_1__ list; } ;
struct carlfw_list_entry {TYPE_2__ h; } ;
struct carlfw {int dummy; } ;
struct carl9170fw_desc_head {int dummy; } ;

/* Variables and functions */
 int carlfw_desc_add (struct carlfw*,struct carl9170fw_desc_head const*,struct carl9170fw_desc_head*,struct carl9170fw_desc_head*) ; 
 struct carlfw_list_entry* carlfw_desc_to_entry (struct carl9170fw_desc_head*) ; 
 struct carl9170fw_desc_head* carlfw_entry_to_desc (struct carlfw_list_entry*) ; 

int carlfw_desc_add_before(struct carlfw *fw,
			   const struct carl9170fw_desc_head *desc,
			   struct carl9170fw_desc_head *pos)
{
	struct carl9170fw_desc_head *prev;
	struct carlfw_list_entry *prev_entry;

	prev_entry = carlfw_desc_to_entry(pos);

	prev = carlfw_entry_to_desc((struct carlfw_list_entry *) prev_entry->h.list.prev);

	return carlfw_desc_add(fw, desc, prev, pos);
}