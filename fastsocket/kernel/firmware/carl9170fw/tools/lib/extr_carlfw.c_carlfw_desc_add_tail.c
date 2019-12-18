#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct carlfw_list_entry {TYPE_1__ h; } ;
struct carlfw {int /*<<< orphan*/  desc_list; } ;
struct carl9170fw_desc_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct carlfw_list_entry*) ; 
 int PTR_ERR (struct carlfw_list_entry*) ; 
 struct carlfw_list_entry* __carlfw_entry_add_prepare (struct carlfw*,struct carl9170fw_desc_head const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int carlfw_desc_add_tail(struct carlfw *fw,
	const struct carl9170fw_desc_head *desc)
{
	struct carlfw_list_entry *tmp;

	tmp = __carlfw_entry_add_prepare(fw, desc);
	if (IS_ERR(tmp))
		return PTR_ERR(tmp);

	list_add_tail(&tmp->h.list, &fw->desc_list);
	return 0;
}