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
struct qeth_reply {struct qeth_card* card; int /*<<< orphan*/  received; int /*<<< orphan*/  refcnt; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct qeth_reply* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qeth_reply *qeth_alloc_reply(struct qeth_card *card)
{
	struct qeth_reply *reply;

	reply = kzalloc(sizeof(struct qeth_reply), GFP_ATOMIC);
	if (reply) {
		atomic_set(&reply->refcnt, 1);
		atomic_set(&reply->received, 0);
		reply->card = card;
	};
	return reply;
}