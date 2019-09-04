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
struct proto_input_entry {scalar_t__ protocol; struct proto_input_entry* next; int /*<<< orphan*/  (* detached ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct proto_input_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 struct proto_input_entry** proto_hash ; 
 int proto_hash_value (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void
proto_delayed_attach(struct proto_input_entry *entry)
{
	struct proto_input_entry *next_entry;

	for (next_entry = entry->next; entry != NULL; entry = next_entry) {
		struct proto_input_entry *exist;
		int hash_slot;

		hash_slot = proto_hash_value(entry->protocol);
		next_entry = entry->next;

		for (exist = proto_hash[hash_slot]; exist != NULL;
		    exist = exist->next) {
			if (exist->protocol == entry->protocol)
				break;
		}

		/* If the entry already exists, call detached and dispose */
		if (exist != NULL) {
			if (entry->detached)
				entry->detached(entry->protocol);
			FREE(entry, M_IFADDR);
		} else {
			entry->next = proto_hash[hash_slot];
			proto_hash[hash_slot] = entry;
		}
	}
}