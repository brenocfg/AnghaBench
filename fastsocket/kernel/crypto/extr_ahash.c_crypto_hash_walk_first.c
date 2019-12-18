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
struct crypto_hash_walk {int /*<<< orphan*/  flags; int /*<<< orphan*/  sg; int /*<<< orphan*/  alignmask; int /*<<< orphan*/  total; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ahash_request {TYPE_1__ base; int /*<<< orphan*/  src; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ahash_alignmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int hash_walk_new_entry (struct crypto_hash_walk*) ; 

int crypto_hash_walk_first(struct ahash_request *req,
			   struct crypto_hash_walk *walk)
{
	walk->total = req->nbytes;

	if (!walk->total)
		return 0;

	walk->alignmask = crypto_ahash_alignmask(crypto_ahash_reqtfm(req));
	walk->sg = req->src;
	walk->flags = req->base.flags;

	return hash_walk_new_entry(walk);
}