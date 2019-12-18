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
struct sctp_hashbucket {int /*<<< orphan*/  lock; int /*<<< orphan*/  chain; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;
struct sctp_ep_common {size_t hashent; int /*<<< orphan*/  node; TYPE_1__ bind_addr; } ;
struct sctp_endpoint {struct sctp_ep_common base; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sctp_ep_hashfn (int /*<<< orphan*/ ) ; 
 struct sctp_hashbucket* sctp_ep_hashtable ; 
 int /*<<< orphan*/  sctp_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sctp_hash_endpoint(struct sctp_endpoint *ep)
{
	struct sctp_ep_common *epb;
	struct sctp_hashbucket *head;

	epb = &ep->base;

	epb->hashent = sctp_ep_hashfn(epb->bind_addr.port);
	head = &sctp_ep_hashtable[epb->hashent];

	sctp_write_lock(&head->lock);
	hlist_add_head(&epb->node, &head->chain);
	sctp_write_unlock(&head->lock);
}