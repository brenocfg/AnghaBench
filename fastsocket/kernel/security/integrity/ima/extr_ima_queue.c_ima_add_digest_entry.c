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
struct ima_template_entry {int /*<<< orphan*/  digest; } ;
struct ima_queue_entry {int /*<<< orphan*/  hnext; int /*<<< orphan*/  later; struct ima_template_entry* entry; } ;
struct TYPE_2__ {int /*<<< orphan*/ * queue; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ima_hash_key (int /*<<< orphan*/ ) ; 
 TYPE_1__ ima_htable ; 
 int /*<<< orphan*/  ima_measurements ; 
 struct ima_queue_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ima_add_digest_entry(struct ima_template_entry *entry)
{
	struct ima_queue_entry *qe;
	unsigned int key;

	qe = kmalloc(sizeof(*qe), GFP_KERNEL);
	if (qe == NULL) {
		pr_err("IMA: OUT OF MEMORY ERROR creating queue entry.\n");
		return -ENOMEM;
	}
	qe->entry = entry;

	INIT_LIST_HEAD(&qe->later);
	list_add_tail_rcu(&qe->later, &ima_measurements);

	atomic_long_inc(&ima_htable.len);
	key = ima_hash_key(entry->digest);
	hlist_add_head_rcu(&qe->hnext, &ima_htable.queue[key]);
	return 0;
}