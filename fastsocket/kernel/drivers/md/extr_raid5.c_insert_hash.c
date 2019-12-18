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
struct stripe_head {int /*<<< orphan*/  hash; scalar_t__ sector; } ;
struct r5conf {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long) ; 
 struct hlist_head* stripe_hash (struct r5conf*,scalar_t__) ; 

__attribute__((used)) static inline void insert_hash(struct r5conf *conf, struct stripe_head *sh)
{
	struct hlist_head *hp = stripe_hash(conf, sh->sector);

	pr_debug("insert_hash(), stripe %llu\n",
		(unsigned long long)sh->sector);

	hlist_add_head(&sh->hash, hp);
}