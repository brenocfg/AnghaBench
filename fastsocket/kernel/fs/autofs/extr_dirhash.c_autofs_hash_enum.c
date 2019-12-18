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
struct autofs_dir_ent {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; struct autofs_dir_ent* next; } ;
typedef  int off_t ;

/* Variables and functions */
 int AUTOFS_HASH_SIZE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  autofs_say (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

struct autofs_dir_ent *autofs_hash_enum(const struct autofs_dirhash *dh,
					off_t *ptr, struct autofs_dir_ent *last)
{
	int bucket, ecount, i;
	struct autofs_dir_ent *ent;

	bucket = (*ptr >> 16) - 1;
	ecount = *ptr & 0xffff;

	if ( bucket < 0 ) {
		bucket = ecount = 0;
	} 

	DPRINTK(("autofs_hash_enum: bucket %d, entry %d\n", bucket, ecount));

	ent = last ? last->next : NULL;

	if ( ent ) {
		ecount++;
	} else {
		while  ( bucket < AUTOFS_HASH_SIZE ) {
			ent = dh->h[bucket];
			for ( i = ecount ; ent && i ; i-- )
				ent = ent->next;
			
			if (ent) {
				ecount++; /* Point to *next* entry */
				break;
			}
			
			bucket++; ecount = 0;
		}
	}

#ifdef DEBUG
	if ( !ent )
		printk("autofs_hash_enum: nothing found\n");
	else {
		printk("autofs_hash_enum: found hash %08x, name", ent->hash);
		autofs_say(ent->name,ent->len);
	}
#endif

	*ptr = ((bucket+1) << 16) + ecount;
	return ent;
}