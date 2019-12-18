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
struct crypto_hash_walk {unsigned int alignmask; unsigned int offset; unsigned int entrylen; unsigned int data; int /*<<< orphan*/  pg; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 unsigned int crypto_kmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int hash_walk_next(struct crypto_hash_walk *walk)
{
	unsigned int alignmask = walk->alignmask;
	unsigned int offset = walk->offset;
	unsigned int nbytes = min(walk->entrylen,
				  ((unsigned int)(PAGE_SIZE)) - offset);

	walk->data = crypto_kmap(walk->pg, 0);
	walk->data += offset;

	if (offset & alignmask)
		nbytes = alignmask + 1 - (offset & alignmask);

	walk->entrylen -= nbytes;
	return nbytes;
}