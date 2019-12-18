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
typedef  int /*<<< orphan*/  uwb_rc_cmd_cb_f ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct uwb_rccb {int /*<<< orphan*/  bCommandContext; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct uwb_rc_neh {int /*<<< orphan*/  list_node; int /*<<< orphan*/  context; void* arg; int /*<<< orphan*/  cb; int /*<<< orphan*/  evt; int /*<<< orphan*/  evt_type; struct uwb_rc* rc; TYPE_2__ timer; int /*<<< orphan*/  kref; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct uwb_rc {int /*<<< orphan*/  neh_lock; int /*<<< orphan*/  neh_list; TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct uwb_rc_neh* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __uwb_rc_ctx_get (struct uwb_rc*,struct uwb_rc_neh*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct uwb_rc_neh*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct uwb_rc_neh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uwb_rc_neh_get (struct uwb_rc_neh*) ; 
 int /*<<< orphan*/  uwb_rc_neh_timer ; 

struct uwb_rc_neh *uwb_rc_neh_add(struct uwb_rc *rc, struct uwb_rccb *cmd,
				  u8 expected_type, u16 expected_event,
				  uwb_rc_cmd_cb_f cb, void *arg)
{
	int result;
	unsigned long flags;
	struct device *dev = &rc->uwb_dev.dev;
	struct uwb_rc_neh *neh;

	neh = kzalloc(sizeof(*neh), GFP_KERNEL);
	if (neh == NULL) {
		result = -ENOMEM;
		goto error_kzalloc;
	}

	kref_init(&neh->kref);
	INIT_LIST_HEAD(&neh->list_node);
	init_timer(&neh->timer);
	neh->timer.function = uwb_rc_neh_timer;
	neh->timer.data     = (unsigned long)neh;

	neh->rc = rc;
	neh->evt_type = expected_type;
	neh->evt = cpu_to_le16(expected_event);
	neh->cb = cb;
	neh->arg = arg;

	spin_lock_irqsave(&rc->neh_lock, flags);
	result = __uwb_rc_ctx_get(rc, neh);
	if (result >= 0) {
		cmd->bCommandContext = neh->context;
		list_add_tail(&neh->list_node, &rc->neh_list);
		uwb_rc_neh_get(neh);
	}
	spin_unlock_irqrestore(&rc->neh_lock, flags);
	if (result < 0)
		goto error_ctx_get;

	return neh;

error_ctx_get:
	kfree(neh);
error_kzalloc:
	dev_err(dev, "cannot open handle to radio controller: %d\n", result);
	return ERR_PTR(result);
}