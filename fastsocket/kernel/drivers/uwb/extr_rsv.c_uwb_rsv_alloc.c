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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct uwb_rsv {int /*<<< orphan*/  handle_timeout_work; struct uwb_rc* rc; TYPE_1__ timer; int /*<<< orphan*/  kref; int /*<<< orphan*/  pal_node; int /*<<< orphan*/  rc_node; } ;
struct uwb_rc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct uwb_rsv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rsv_handle_timeout_work ; 
 int /*<<< orphan*/  uwb_rsv_timer ; 

__attribute__((used)) static struct uwb_rsv *uwb_rsv_alloc(struct uwb_rc *rc)
{
	struct uwb_rsv *rsv;

	rsv = kzalloc(sizeof(struct uwb_rsv), GFP_KERNEL);
	if (!rsv)
		return NULL;

	INIT_LIST_HEAD(&rsv->rc_node);
	INIT_LIST_HEAD(&rsv->pal_node);
	kref_init(&rsv->kref);
	init_timer(&rsv->timer);
	rsv->timer.function = uwb_rsv_timer;
	rsv->timer.data     = (unsigned long)rsv;

	rsv->rc = rc;
	INIT_WORK(&rsv->handle_timeout_work, uwb_rsv_handle_timeout_work);

	return rsv;
}