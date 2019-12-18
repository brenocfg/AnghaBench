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
struct cxgbi_sock {scalar_t__ flags; struct cxgbi_device* cdev; int /*<<< orphan*/  callback_lock; int /*<<< orphan*/  retry_timer; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  receive_queue; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; } ;
struct cxgbi_device {scalar_t__ (* csk_alloc_cpls ) (struct cxgbi_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTP_CLOSED ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct cxgbi_sock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,struct cxgbi_sock*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct cxgbi_sock*) ; 

__attribute__((used)) static struct cxgbi_sock *cxgbi_sock_create(struct cxgbi_device *cdev)
{
	struct cxgbi_sock *csk = kzalloc(sizeof(*csk), GFP_NOIO);

	if (!csk) {
		pr_info("alloc csk %zu failed.\n", sizeof(*csk));
		return NULL;
	}

	if (cdev->csk_alloc_cpls(csk) < 0) {
		pr_info("csk 0x%p, alloc cpls failed.\n", csk);
		kfree(csk);
		return NULL;
	}

	spin_lock_init(&csk->lock);
	kref_init(&csk->refcnt);
	skb_queue_head_init(&csk->receive_queue);
	skb_queue_head_init(&csk->write_queue);
	setup_timer(&csk->retry_timer, NULL, (unsigned long)csk);
	rwlock_init(&csk->callback_lock);
	csk->cdev = cdev;
	csk->flags = 0;
	cxgbi_sock_set_state(csk, CTP_CLOSED);

	log_debug(1 << CXGBI_DBG_SOCK, "cdev 0x%p, new csk 0x%p.\n", cdev, csk);

	return csk;
}