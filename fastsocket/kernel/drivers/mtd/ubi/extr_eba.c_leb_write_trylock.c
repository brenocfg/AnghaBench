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
struct ubi_ltree_entry {scalar_t__ users; int /*<<< orphan*/  rb; int /*<<< orphan*/  mutex; } ;
struct ubi_device {int /*<<< orphan*/  ltree_lock; int /*<<< orphan*/  ltree; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubi_ltree_entry*) ; 
 int PTR_ERR (struct ubi_ltree_entry*) ; 
 scalar_t__ down_write_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ubi_ltree_entry*) ; 
 struct ubi_ltree_entry* ltree_add_entry (struct ubi_device*,int,int) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 

__attribute__((used)) static int leb_write_trylock(struct ubi_device *ubi, int vol_id, int lnum)
{
	struct ubi_ltree_entry *le;

	le = ltree_add_entry(ubi, vol_id, lnum);
	if (IS_ERR(le))
		return PTR_ERR(le);
	if (down_write_trylock(&le->mutex))
		return 0;

	/* Contention, cancel */
	spin_lock(&ubi->ltree_lock);
	le->users -= 1;
	ubi_assert(le->users >= 0);
	if (le->users == 0) {
		rb_erase(&le->rb, &ubi->ltree);
		kfree(le);
	}
	spin_unlock(&ubi->ltree_lock);

	return 1;
}