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
struct ubifs_info {int gc_lnum; int /*<<< orphan*/  leb_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LPROPS_TAKEN ; 
 int ubifs_change_one_lp (struct ubifs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 

__attribute__((used)) static int take_gc_lnum(struct ubifs_info *c)
{
	int err;

	if (c->gc_lnum == -1) {
		ubifs_err("no LEB for GC");
		return -EINVAL;
	}

	/* And we have to tell lprops that this LEB is taken */
	err = ubifs_change_one_lp(c, c->gc_lnum, c->leb_size, 0,
				  LPROPS_TAKEN, 0, 0);
	return err;
}