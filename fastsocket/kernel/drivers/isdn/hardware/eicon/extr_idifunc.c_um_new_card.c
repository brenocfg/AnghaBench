#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* request ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int Id; int /*<<< orphan*/  list; TYPE_5__ d; } ;
typedef  TYPE_3__ udiva_card ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
struct TYPE_8__ {int logical_adapter_number; } ;
struct TYPE_9__ {TYPE_1__ info; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_11__ {TYPE_2__ xdi_logical_adapter_number; } ;
typedef  TYPE_4__ IDI_SYNC_REQ ;
typedef  int /*<<< orphan*/  ENTITY ;
typedef  int /*<<< orphan*/  DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_XDI_GET_LOGICAL_ADAPTER_NUMBER ; 
 int /*<<< orphan*/  cards ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* diva_os_malloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  diva_user_mode_idi_create_adapter (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_lock ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void um_new_card(DESCRIPTOR * d)
{
	int adapter_nr = 0;
	udiva_card *card = NULL;
	IDI_SYNC_REQ sync_req;
	diva_os_spin_lock_magic_t old_irql;

	if (!(card = diva_os_malloc(0, sizeof(udiva_card)))) {
		DBG_ERR(("cannot get buffer for card"));
		return;
	}
	memcpy(&card->d, d, sizeof(DESCRIPTOR));
	sync_req.xdi_logical_adapter_number.Req = 0;
	sync_req.xdi_logical_adapter_number.Rc =
	    IDI_SYNC_REQ_XDI_GET_LOGICAL_ADAPTER_NUMBER;
	card->d.request((ENTITY *) & sync_req);
	adapter_nr =
	    sync_req.xdi_logical_adapter_number.info.logical_adapter_number;
	card->Id = adapter_nr;
	if (!(diva_user_mode_idi_create_adapter(d, adapter_nr))) {
		diva_os_enter_spin_lock(&ll_lock, &old_irql, "add card");
		list_add_tail(&card->list, &cards);
		diva_os_leave_spin_lock(&ll_lock, &old_irql, "add card");
	} else {
		DBG_ERR(("could not create user mode idi card %d",
			 adapter_nr));
		diva_os_free(0, card);
	}
}