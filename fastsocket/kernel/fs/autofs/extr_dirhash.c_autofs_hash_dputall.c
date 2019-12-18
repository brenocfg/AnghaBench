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
struct autofs_dirhash {struct autofs_dir_ent** h; } ;
struct autofs_dir_ent {int /*<<< orphan*/ * dentry; struct autofs_dir_ent* next; } ;

/* Variables and functions */
 int AUTOFS_HASH_SIZE ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ *) ; 

void autofs_hash_dputall(struct autofs_dirhash *dh)
{
	int i;
	struct autofs_dir_ent *ent;

	for ( i = 0 ; i < AUTOFS_HASH_SIZE ; i++ ) {
		for ( ent = dh->h[i] ; ent ; ent = ent->next ) {
			if ( ent->dentry ) {
				dput(ent->dentry);
				ent->dentry = NULL;
			}
		}
	}
}