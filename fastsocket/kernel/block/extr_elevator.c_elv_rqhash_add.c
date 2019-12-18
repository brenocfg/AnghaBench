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
struct request_queue {struct elevator_queue* elevator; } ;
struct request {int /*<<< orphan*/  hash; } ;
struct elevator_queue {int /*<<< orphan*/ * hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 size_t ELV_HASH_FN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELV_ON_HASH (struct request*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_hash_key (struct request*) ; 

__attribute__((used)) static void elv_rqhash_add(struct request_queue *q, struct request *rq)
{
	struct elevator_queue *e = q->elevator;

	BUG_ON(ELV_ON_HASH(rq));
	hlist_add_head(&rq->hash, &e->hash[ELV_HASH_FN(rq_hash_key(rq))]);
}