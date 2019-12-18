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
struct sctp_bind_hashbucket {int /*<<< orphan*/  chain; } ;
struct sctp_bind_bucket {unsigned short port; int /*<<< orphan*/  node; int /*<<< orphan*/  owner; scalar_t__ fastreuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_bucket ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sctp_bind_bucket* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_bucket_cachep ; 

__attribute__((used)) static struct sctp_bind_bucket *sctp_bucket_create(
	struct sctp_bind_hashbucket *head, unsigned short snum)
{
	struct sctp_bind_bucket *pp;

	pp = kmem_cache_alloc(sctp_bucket_cachep, GFP_ATOMIC);
	if (pp) {
		SCTP_DBG_OBJCNT_INC(bind_bucket);
		pp->port = snum;
		pp->fastreuse = 0;
		INIT_HLIST_HEAD(&pp->owner);
		hlist_add_head(&pp->node, &head->chain);
	}
	return pp;
}