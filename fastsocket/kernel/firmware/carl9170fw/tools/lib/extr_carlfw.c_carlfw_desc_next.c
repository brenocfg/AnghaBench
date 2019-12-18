#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ next; } ;
struct TYPE_5__ {TYPE_1__ list; } ;
struct carlfw_list_entry {TYPE_2__ h; } ;
struct carlfw {int /*<<< orphan*/  desc_list; } ;
struct carl9170fw_desc_head {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct carlfw_list_entry* carlfw_desc_to_entry (struct carl9170fw_desc_head*) ; 
 void* carlfw_entry_to_desc (struct carlfw_list_entry*) ; 
 TYPE_3__ h ; 
 scalar_t__ list_at_tail (struct carlfw_list_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *carlfw_desc_next(struct carlfw *fw,
		       struct carl9170fw_desc_head *pos)
{
	struct carlfw_list_entry *entry;

	if (!pos)
		entry = (struct carlfw_list_entry *) &fw->desc_list;
	else
		entry = carlfw_desc_to_entry(pos);

	if (list_at_tail(entry, &fw->desc_list, h.list))
		return NULL;

	entry = (struct carlfw_list_entry *) entry->h.list.next;

	return carlfw_entry_to_desc(entry);
}