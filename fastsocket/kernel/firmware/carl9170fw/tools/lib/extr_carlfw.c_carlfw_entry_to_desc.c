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
struct carl9170fw_desc_head {int dummy; } ;
struct carlfw_list_entry {struct carl9170fw_desc_head head; } ;

/* Variables and functions */

__attribute__((used)) static inline struct carl9170fw_desc_head *carlfw_entry_to_desc(struct carlfw_list_entry *entry)
{
	return &entry->head;
}