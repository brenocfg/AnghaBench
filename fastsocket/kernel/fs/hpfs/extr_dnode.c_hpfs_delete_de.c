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
struct super_block {int dummy; } ;
struct hpfs_dirent {int length; scalar_t__ last; } ;
struct dnode {int first_free; int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int /*<<< orphan*/  de_next_de (struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct hpfs_dirent*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hpfs_delete_de(struct super_block *s, struct dnode *d,
			   struct hpfs_dirent *de)
{
	if (de->last) {
		hpfs_error(s, "attempt to delete last dirent in dnode %08x", d->self);
		return;
	}
	d->first_free -= de->length;
	memmove(de, de_next_de(de), d->first_free + (char *)d - (char *)de);
}