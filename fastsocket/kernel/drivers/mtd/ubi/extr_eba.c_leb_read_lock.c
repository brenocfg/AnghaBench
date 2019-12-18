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
struct ubi_ltree_entry {int /*<<< orphan*/  mutex; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubi_ltree_entry*) ; 
 int PTR_ERR (struct ubi_ltree_entry*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct ubi_ltree_entry* ltree_add_entry (struct ubi_device*,int,int) ; 

__attribute__((used)) static int leb_read_lock(struct ubi_device *ubi, int vol_id, int lnum)
{
	struct ubi_ltree_entry *le;

	le = ltree_add_entry(ubi, vol_id, lnum);
	if (IS_ERR(le))
		return PTR_ERR(le);
	down_read(&le->mutex);
	return 0;
}