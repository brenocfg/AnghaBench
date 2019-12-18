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
struct scatterlist {scalar_t__ length; int /*<<< orphan*/  offset; } ;
struct crypto_hash_walk {scalar_t__ entrylen; scalar_t__ total; int /*<<< orphan*/  offset; int /*<<< orphan*/  pg; struct scatterlist* sg; } ;

/* Variables and functions */
 int hash_walk_next (struct crypto_hash_walk*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static int hash_walk_new_entry(struct crypto_hash_walk *walk)
{
	struct scatterlist *sg;

	sg = walk->sg;
	walk->pg = sg_page(sg);
	walk->offset = sg->offset;
	walk->entrylen = sg->length;

	if (walk->entrylen > walk->total)
		walk->entrylen = walk->total;
	walk->total -= walk->entrylen;

	return hash_walk_next(walk);
}