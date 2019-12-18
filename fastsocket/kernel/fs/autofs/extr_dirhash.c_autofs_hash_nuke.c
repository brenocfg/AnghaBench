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
struct TYPE_2__ {struct autofs_dir_ent** h; } ;
struct autofs_sb_info {TYPE_1__ dirhash; } ;
struct autofs_dir_ent {struct autofs_dir_ent* name; scalar_t__ dentry; struct autofs_dir_ent* next; } ;

/* Variables and functions */
 int AUTOFS_HASH_SIZE ; 
 int /*<<< orphan*/  dput (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct autofs_dir_ent*) ; 

void autofs_hash_nuke(struct autofs_sb_info *sbi)
{
	int i;
	struct autofs_dir_ent *ent, *nent;

	for ( i = 0 ; i < AUTOFS_HASH_SIZE ; i++ ) {
		for ( ent = sbi->dirhash.h[i] ; ent ; ent = nent ) {
			nent = ent->next;
			if ( ent->dentry )
				dput(ent->dentry);
			kfree(ent->name);
			kfree(ent);
		}
	}
}