#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t dword ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
struct TYPE_8__ {int last_dbgMask; int dbgMask; TYPE_2__* pIdiLib; int /*<<< orphan*/  (* request ) (int /*<<< orphan*/ *) ;scalar_t__ request_pending; TYPE_1__* hDbg; } ;
struct TYPE_7__ {int /*<<< orphan*/  hLib; scalar_t__ (* DivaSTraceGetHandle ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {size_t dbgMask; } ;
typedef  int /*<<< orphan*/  ENTITY ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 TYPE_3__* clients ; 
 int /*<<< orphan*/  dbg_adapter_lock ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/  diva_change_management_debug_mask (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ) ; 

int diva_set_driver_dbg_mask (dword id, dword mask) {
  diva_os_spin_lock_magic_t old_irql, old_irql1;
  int ret = -1;
  

  if (!id || (id >= ARRAY_SIZE(clients))) {
    return (-1);
  }

  diva_os_enter_spin_lock (&dbg_adapter_lock, &old_irql1, "dbg mask");
  diva_os_enter_spin_lock (&dbg_q_lock, &old_irql, "dbg mask");

  if (clients[id].hDbg) {
    dword old_mask = clients[id].hDbg->dbgMask;
    mask &= 0x7fffffff;
    clients[id].hDbg->dbgMask = mask;
    clients[id].last_dbgMask = (clients[id].hDbg->dbgMask | clients[id].dbgMask);
    ret = 4;
    diva_change_management_debug_mask (&clients[id], old_mask);
  }


  diva_os_leave_spin_lock (&dbg_q_lock, &old_irql, "dbg mask");

  if (clients[id].request_pending) {
    clients[id].request_pending = 0;
    (*(clients[id].request))((ENTITY*)(*(clients[id].pIdiLib->DivaSTraceGetHandle))(clients[id].pIdiLib->hLib));
  }

  diva_os_leave_spin_lock (&dbg_adapter_lock, &old_irql1, "dbg mask");

  return (ret);
}