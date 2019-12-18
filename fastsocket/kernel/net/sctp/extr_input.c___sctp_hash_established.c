#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sctp_hashbucket {int /*<<< orphan*/  lock; int /*<<< orphan*/  chain; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct sctp_ep_common {size_t hashent; int /*<<< orphan*/  node; TYPE_1__ bind_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct sctp_association {TYPE_2__ peer; struct sctp_ep_common base; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sctp_assoc_hashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_hashbucket* sctp_assoc_hashtable ; 
 int /*<<< orphan*/  sctp_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sctp_hash_established(struct sctp_association *asoc)
{
	struct sctp_ep_common *epb;
	struct sctp_hashbucket *head;

	epb = &asoc->base;

	/* Calculate which chain this entry will belong to. */
	epb->hashent = sctp_assoc_hashfn(epb->bind_addr.port, asoc->peer.port);

	head = &sctp_assoc_hashtable[epb->hashent];

	sctp_write_lock(&head->lock);
	hlist_add_head(&epb->node, &head->chain);
	sctp_write_unlock(&head->lock);
}