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
struct idmap_hashtable {TYPE_1__* h_entries; } ;
struct TYPE_2__ {struct TYPE_2__* ih_name; } ;

/* Variables and functions */
 int IDMAP_HASH_SZ ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void
idmap_free_hashtable(struct idmap_hashtable *h)
{
	int i;

	if (h->h_entries == NULL)
		return;
	for (i = 0; i < IDMAP_HASH_SZ; i++)
		kfree(h->h_entries[i].ih_name);
	kfree(h->h_entries);
}