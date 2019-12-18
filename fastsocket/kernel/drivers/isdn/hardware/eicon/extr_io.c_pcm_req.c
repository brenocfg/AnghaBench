#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct pc_maint {int /*<<< orphan*/  req; } ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
struct TYPE_18__ {int /*<<< orphan*/  rc; int /*<<< orphan*/  req; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* ram_in_buffer ) (TYPE_4__*,TYPE_8__*,struct pc_maint*,int) ;scalar_t__ (* ram_in ) (TYPE_4__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ram_out ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  Ind; } ;
struct TYPE_14__ {scalar_t__ Card; } ;
struct TYPE_15__ {int pcm_pending; int trapped; int /*<<< orphan*/  ANum; int /*<<< orphan*/  (* os_trap_nfy_Fnc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* trapFnc ) (TYPE_2__*) ;TYPE_8__* pcm; int /*<<< orphan*/  data_spin_lock; int /*<<< orphan*/ * pcm_data; int /*<<< orphan*/  req_soft_isr; TYPE_1__ Properties; TYPE_4__ a; } ;
typedef  TYPE_2__* PISDN_ADAPTER ;
typedef  TYPE_3__ ENTITY ;
typedef  TYPE_4__ ADAPTER ;

/* Variables and functions */
 scalar_t__ CARD_MAE ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_schedule_soft_isr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diva_os_sleep (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,TYPE_8__*,struct pc_maint*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcm_req (PISDN_ADAPTER IoAdapter, ENTITY *e)
{
 diva_os_spin_lock_magic_t OldIrql ;
 int              i, rc ;
 ADAPTER         *a = &IoAdapter->a ;
 struct pc_maint *pcm = (struct pc_maint *)&e->Ind ;
/*
 * special handling of I/O based card interface
 * the memory access isn't an atomic operation !
 */
 if ( IoAdapter->Properties.Card == CARD_MAE )
 {
  diva_os_enter_spin_lock (&IoAdapter->data_spin_lock,
               &OldIrql,
               "data_pcm_1");
  IoAdapter->pcm_data = (void *)pcm;
  IoAdapter->pcm_pending = 1;
  diva_os_schedule_soft_isr (&IoAdapter->req_soft_isr);
  diva_os_leave_spin_lock (&IoAdapter->data_spin_lock,
               &OldIrql,
               "data_pcm_1");
  for ( rc = 0, i = (IoAdapter->trapped ? 3000 : 250) ; !rc && (i > 0) ; --i )
  {
   diva_os_sleep (1) ;
   if (IoAdapter->pcm_pending == 3) {
    diva_os_enter_spin_lock (&IoAdapter->data_spin_lock,
                 &OldIrql,
                 "data_pcm_3");
    IoAdapter->pcm_pending = 0;
    IoAdapter->pcm_data    = NULL ;
    diva_os_leave_spin_lock (&IoAdapter->data_spin_lock,
                 &OldIrql,
                 "data_pcm_3");
    return ;
   }
   diva_os_enter_spin_lock (&IoAdapter->data_spin_lock,
                &OldIrql,
                "data_pcm_2");
   diva_os_schedule_soft_isr (&IoAdapter->req_soft_isr);
   diva_os_leave_spin_lock (&IoAdapter->data_spin_lock,
                &OldIrql,
                "data_pcm_2");
  }
  diva_os_enter_spin_lock (&IoAdapter->data_spin_lock,
               &OldIrql,
               "data_pcm_4");
  IoAdapter->pcm_pending = 0;
  IoAdapter->pcm_data    = NULL ;
  diva_os_leave_spin_lock (&IoAdapter->data_spin_lock,
               &OldIrql,
               "data_pcm_4");
  goto Trapped ;
 }
/*
 * memory based shared ram is accessible from different
 * processors without disturbing concurrent processes.
 */
 a->ram_out (a, &IoAdapter->pcm->rc, 0) ;
 a->ram_out (a, &IoAdapter->pcm->req, pcm->req) ;
 for ( i = (IoAdapter->trapped ? 3000 : 250) ; --i > 0 ; )
 {
  diva_os_sleep (1) ;
  rc = (int)(a->ram_in (a, &IoAdapter->pcm->rc)) ;
  if ( rc )
  {
   a->ram_in_buffer (a, IoAdapter->pcm, pcm, sizeof(*pcm)) ;
   return ;
  }
 }
Trapped:
 if ( IoAdapter->trapFnc )
 {
    int trapped = IoAdapter->trapped;
  IoAdapter->trapFnc (IoAdapter) ;
    /*
      Firs trap, also notify user if supported
     */
    if (!trapped && IoAdapter->trapped && IoAdapter->os_trap_nfy_Fnc) {
      (*(IoAdapter->os_trap_nfy_Fnc))(IoAdapter, IoAdapter->ANum);
    }
 }
}