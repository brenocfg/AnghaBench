#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  word ;
typedef  TYPE_1__* pDbgHandle ;
typedef  void* dword ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
struct TYPE_9__ {int data_length; scalar_t__ di_cpu; scalar_t__ drv_id; int /*<<< orphan*/  dli; int /*<<< orphan*/  facility; void* time_usec; void* time_sec; scalar_t__ sequence; } ;
typedef  TYPE_2__ diva_dbg_entry_head_t ;
typedef  scalar_t__ byte ;
struct TYPE_10__ {int id; } ;
typedef  TYPE_3__ _OldDbgHandle_ ;
struct TYPE_11__ {int /*<<< orphan*/  last_dbgMask; int /*<<< orphan*/  dbgMask; int /*<<< orphan*/  drvName; void* usec; void* sec; TYPE_1__* hDbg; } ;
struct TYPE_8__ {scalar_t__ id; scalar_t__ Registered; char* drvName; scalar_t__ Version; struct TYPE_8__* next; int /*<<< orphan*/  dbg_old; void* dbg_irq; int /*<<< orphan*/  dbg_ev; void* dbg_prt; int /*<<< orphan*/  dbg_end; int /*<<< orphan*/  dbgMask; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__*) ; 
 scalar_t__ DBG_HANDLE_REG_NEW ; 
 scalar_t__ DBG_MAGIC ; 
 int /*<<< orphan*/  DI_deregister ; 
 void* DI_format_locked ; 
 int /*<<< orphan*/  DI_format_old ; 
 int /*<<< orphan*/  DLI_REG ; 
 int /*<<< orphan*/  DiProcessEventLog ; 
 int /*<<< orphan*/  MSG_TYPE_STRING ; 
 TYPE_6__* clients ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/  dbg_queue ; 
 int /*<<< orphan*/  dbg_sequence ; 
 int /*<<< orphan*/  diva_maint_wakeup_read () ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_get_time (void**,void**) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,char*,int) ; 
 scalar_t__ queueAllocMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queueCompleteMsg (TYPE_2__*) ; 
 int /*<<< orphan*/  queueFreeMsg (int /*<<< orphan*/ ) ; 
 scalar_t__ queuePeekMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void DI_register (void *arg) {
  diva_os_spin_lock_magic_t old_irql;
  dword sec, usec;
  pDbgHandle  	hDbg ;
  int id, free_id = -1, best_id = 0;
  
  diva_os_get_time (&sec, &usec);

	hDbg = (pDbgHandle)arg ;
  /*
    Check for bad args, specially for the old obsolete debug handle
    */
  if ((hDbg == NULL) ||
      ((hDbg->id == 0) && (((_OldDbgHandle_ *)hDbg)->id == -1)) ||
      (hDbg->Registered != 0)) {
		return ;
  }

  diva_os_enter_spin_lock (&dbg_q_lock, &old_irql, "register");

  for (id = 1; id < ARRAY_SIZE(clients); id++) {
    if (clients[id].hDbg == hDbg) {
      /*
        driver already registered
        */
      diva_os_leave_spin_lock (&dbg_q_lock, &old_irql, "register");
      return;
    }
    if (clients[id].hDbg) { /* slot is busy */
      continue;
    }
    free_id = id;
    if (!strcmp (clients[id].drvName, hDbg->drvName)) {
      /*
        This driver was already registered with this name
        and slot is still free - reuse it
        */
      best_id = 1;
      break;
    }
    if (!clients[id].hDbg) { /* slot is busy */
      break;
    }
  }

  if (free_id != -1) {
    diva_dbg_entry_head_t* pmsg = NULL;
    int len;
    char tmp[256];
    word size;

    /*
      Register new driver with id == free_id
      */
    clients[free_id].hDbg = hDbg;
    clients[free_id].sec  = sec;
    clients[free_id].usec = usec;
    strcpy (clients[free_id].drvName, hDbg->drvName);

    clients[free_id].dbgMask = hDbg->dbgMask;
    if (best_id) {
      hDbg->dbgMask |= clients[free_id].last_dbgMask;
    } else {
      clients[free_id].last_dbgMask = 0;
    }

    hDbg->Registered = DBG_HANDLE_REG_NEW ;
    hDbg->id         = (byte)free_id;
    hDbg->dbg_end    = DI_deregister;
    hDbg->dbg_prt    = DI_format_locked;
    hDbg->dbg_ev     = DiProcessEventLog;
    hDbg->dbg_irq    = DI_format_locked;
    if (hDbg->Version > 0) {
      hDbg->dbg_old  = DI_format_old;
    }
    hDbg->next       = (pDbgHandle)DBG_MAGIC;

    /*
      Log driver register, MAINT driver ID is '0'
      */
    len = sprintf (tmp, "DIMAINT - drv # %d = '%s' registered",
                   free_id, hDbg->drvName);

    while (!(pmsg = (diva_dbg_entry_head_t*)queueAllocMsg (dbg_queue,
                                        (word)(len+1+sizeof(*pmsg))))) {
      if ((pmsg = (diva_dbg_entry_head_t*)queuePeekMsg (dbg_queue, &size))) {
        queueFreeMsg (dbg_queue);
      } else {
        break;
      }
    }

    if (pmsg) {
      pmsg->sequence    = dbg_sequence++;
      pmsg->time_sec    = sec;
      pmsg->time_usec   = usec;
      pmsg->facility    = MSG_TYPE_STRING;
      pmsg->dli         = DLI_REG;
      pmsg->drv_id      = 0; /* id 0 - DIMAINT */
      pmsg->di_cpu      = 0;
      pmsg->data_length = len+1;

      memcpy (&pmsg[1], tmp, len+1);
		  queueCompleteMsg (pmsg);
      diva_maint_wakeup_read();
    }
  }

  diva_os_leave_spin_lock (&dbg_q_lock, &old_irql, "register");
}