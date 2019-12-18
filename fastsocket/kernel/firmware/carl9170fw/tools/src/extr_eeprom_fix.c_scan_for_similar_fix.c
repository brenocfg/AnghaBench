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
struct carl9170fw_fix_entry {scalar_t__ address; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct carl9170fw_fix_desc {struct carl9170fw_fix_entry* data; TYPE_1__ head; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct carl9170fw_fix_entry *
scan_for_similar_fix(struct carl9170fw_fix_desc *fix, __le32 address)
{
	unsigned int i, entries;

	entries = (le16_to_cpu(fix->head.length) - sizeof(*fix)) /
		   sizeof(struct carl9170fw_fix_entry);

	for (i = 0; i < entries; i++) {
		if (address == fix->data[i].address)
			return &fix->data[i];
	}

	return NULL;
}