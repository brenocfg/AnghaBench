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
struct scatterlist {int dummy; } ;
struct hash_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct crypto_hash_walk {unsigned int total; int /*<<< orphan*/  flags; struct scatterlist* sg; int /*<<< orphan*/  alignmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_alignmask (int /*<<< orphan*/ ) ; 
 int hash_walk_new_entry (struct crypto_hash_walk*) ; 

int crypto_hash_walk_first_compat(struct hash_desc *hdesc,
				  struct crypto_hash_walk *walk,
				  struct scatterlist *sg, unsigned int len)
{
	walk->total = len;

	if (!walk->total)
		return 0;

	walk->alignmask = crypto_hash_alignmask(hdesc->tfm);
	walk->sg = sg;
	walk->flags = hdesc->flags;

	return hash_walk_new_entry(walk);
}