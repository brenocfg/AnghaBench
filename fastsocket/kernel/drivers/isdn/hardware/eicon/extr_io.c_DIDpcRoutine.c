#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct pc_maint {int /*<<< orphan*/  req; } ;
struct _diva_os_soft_isr {int dummy; } ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
typedef  int /*<<< orphan*/  diva_os_atomic_t ;
struct TYPE_14__ {int /*<<< orphan*/  rc; int /*<<< orphan*/  req; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* ram_in_buffer ) (TYPE_2__*,TYPE_4__*,struct pc_maint*,int) ;scalar_t__ (* ram_in ) (TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ram_out ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int pcm_pending; int /*<<< orphan*/  data_spin_lock; TYPE_4__* pcm; scalar_t__ pcm_data; int /*<<< orphan*/  (* out ) (TYPE_2__*) ;int /*<<< orphan*/  (* clr_irq ) (TYPE_2__*) ;int /*<<< orphan*/  (* dpc ) (TYPE_2__*) ;int /*<<< orphan*/  Unavailable; scalar_t__ (* tst_irq ) (TYPE_2__*) ;int /*<<< orphan*/  in_dpc; TYPE_2__ a; } ;
typedef  TYPE_1__* PISDN_ADAPTER ;
typedef  TYPE_2__ ADAPTER ;

/* Variables and functions */
 scalar_t__ diva_os_atomic_decrement (int /*<<< orphan*/ *) ; 
 int diva_os_atomic_increment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_2__*,TYPE_4__*,struct pc_maint*,int) ; 

void DIDpcRoutine (struct _diva_os_soft_isr* psoft_isr, void* Context) {
 PISDN_ADAPTER IoAdapter  = (PISDN_ADAPTER)Context ;
 ADAPTER* a        = &IoAdapter->a ;
 diva_os_atomic_t* pin_dpc = &IoAdapter->in_dpc;
 if (diva_os_atomic_increment (pin_dpc) == 1) {
  do {
   if ( IoAdapter->tst_irq (a) )
   {
    if ( !IoAdapter->Unavailable )
     IoAdapter->dpc (a) ;
    IoAdapter->clr_irq (a) ;
   }
   IoAdapter->out (a) ;
  } while (diva_os_atomic_decrement (pin_dpc) > 0);
  /* ----------------------------------------------------------------
    Look for XLOG request (cards with indirect addressing)
    ---------------------------------------------------------------- */
  if (IoAdapter->pcm_pending) {
   struct pc_maint *pcm;
   diva_os_spin_lock_magic_t OldIrql ;
   diva_os_enter_spin_lock (&IoAdapter->data_spin_lock,
                &OldIrql,
                "data_dpc");
   pcm = (struct pc_maint *)IoAdapter->pcm_data;
   switch (IoAdapter->pcm_pending) {
    case 1: /* ask card for XLOG */
     a->ram_out (a, &IoAdapter->pcm->rc, 0) ;
     a->ram_out (a, &IoAdapter->pcm->req, pcm->req) ;
     IoAdapter->pcm_pending = 2;
     break;
    case 2: /* Try to get XLOG from the card */
     if ((int)(a->ram_in (a, &IoAdapter->pcm->rc))) {
      a->ram_in_buffer (a, IoAdapter->pcm, pcm, sizeof(*pcm)) ;
      IoAdapter->pcm_pending = 3;
     }
     break;
    case 3: /* let XDI recovery XLOG */
     break;
   }
   diva_os_leave_spin_lock (&IoAdapter->data_spin_lock,
                &OldIrql,
                "data_dpc");
  }
  /* ---------------------------------------------------------------- */
 }
}