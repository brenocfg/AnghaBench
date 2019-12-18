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
struct idmap_hashtable {int /*<<< orphan*/ * h_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDMAP_HASH_SZ ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
idmap_alloc_hashtable(struct idmap_hashtable *h)
{
	if (h->h_entries != NULL)
		return;
	h->h_entries = kcalloc(IDMAP_HASH_SZ,
			sizeof(*h->h_entries),
			GFP_KERNEL);
}