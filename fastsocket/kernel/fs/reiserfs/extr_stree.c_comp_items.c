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
struct treepath {int dummy; } ;
struct item_head {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_IS_IN_TREE (struct buffer_head*) ; 
 scalar_t__ B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  IH_SIZE ; 
 scalar_t__ PATH_LAST_POSITION (struct treepath const*) ; 
 struct buffer_head* PATH_PLAST_BUFFER (struct treepath const*) ; 
 struct item_head* get_ih (struct treepath const*) ; 
 int memcmp (struct item_head const*,struct item_head*,int /*<<< orphan*/ ) ; 

int comp_items(const struct item_head *stored_ih, const struct treepath *path)
{
	struct buffer_head *bh = PATH_PLAST_BUFFER(path);
	struct item_head *ih;

	/* Last buffer at the path is not in the tree. */
	if (!B_IS_IN_TREE(bh))
		return 1;

	/* Last path position is invalid. */
	if (PATH_LAST_POSITION(path) >= B_NR_ITEMS(bh))
		return 1;

	/* we need only to know, whether it is the same item */
	ih = get_ih(path);
	return memcmp(stored_ih, ih, IH_SIZE);
}