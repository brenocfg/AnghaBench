#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* request ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_8__ {TYPE_2__ info; TYPE_1__ e; } ;
struct TYPE_9__ {TYPE_3__ didd_notify; } ;
typedef  TYPE_4__ IDI_SYNC_REQ ;
typedef  int /*<<< orphan*/  ENTITY ;

/* Variables and functions */
 TYPE_5__ DAdapter ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER_NOTIFY ; 
 int /*<<< orphan*/  notify_handle ; 
 int /*<<< orphan*/  stop_dbg () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void divacapi_disconnect_didd(void)
{
	IDI_SYNC_REQ req;

	stop_dbg();

	req.didd_notify.e.Req = 0;
	req.didd_notify.e.Rc = IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER_NOTIFY;
	req.didd_notify.info.handle = notify_handle;
	DAdapter.request((ENTITY *) & req);
}