#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  word ;
typedef  void* dword ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
struct TYPE_11__ {int data_length; scalar_t__ di_cpu; scalar_t__ drv_id; int /*<<< orphan*/  dli; int /*<<< orphan*/  facility; void* time_usec; void* time_sec; scalar_t__ sequence; } ;
typedef  TYPE_2__ diva_dbg_entry_head_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_13__ {char* drvName; } ;
struct TYPE_14__ {int dma_handle; TYPE_5__ Dbg; int /*<<< orphan*/ * request; scalar_t__ request_pending; int /*<<< orphan*/ * hDbg; int /*<<< orphan*/ * pmem; TYPE_1__* pIdiLib; } ;
struct TYPE_12__ {int /*<<< orphan*/ * request; } ;
struct TYPE_10__ {int /*<<< orphan*/  hLib; int /*<<< orphan*/  (* DivaSTraceLibraryFinit ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ DESCRIPTOR ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_8__*) ; 
 int /*<<< orphan*/  DLI_REG ; 
 int /*<<< orphan*/  MSG_TYPE_STRING ; 
 TYPE_8__* clients ; 
 int /*<<< orphan*/  dbg_adapter_lock ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/  dbg_queue ; 
 int /*<<< orphan*/  dbg_sequence ; 
 int /*<<< orphan*/  diva_free_dma_descriptor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  diva_maint_wakeup_read () ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diva_os_get_time (void**,void**) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int,int) ; 
 scalar_t__ queueAllocMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queueCompleteMsg (TYPE_2__*) ; 
 int /*<<< orphan*/  queueFreeMsg (int /*<<< orphan*/ ) ; 
 scalar_t__ queuePeekMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void diva_mnt_remove_xdi_adapter (const DESCRIPTOR* d) {
  diva_os_spin_lock_magic_t old_irql, old_irql1;
  dword sec, usec;
  int i;
  word size;
  byte* pmem = NULL;

  diva_os_get_time (&sec, &usec);

  diva_os_enter_spin_lock (&dbg_adapter_lock, &old_irql1, "read");
  diva_os_enter_spin_lock (&dbg_q_lock, &old_irql, "read");

  for (i = 1; i < ARRAY_SIZE(clients); i++) {
    if (clients[i].hDbg && (clients[i].request == d->request)) {
      diva_dbg_entry_head_t* pmsg;
      char tmp[256];
      int len;

      if (clients[i].pIdiLib) {
        (*(clients[i].pIdiLib->DivaSTraceLibraryFinit))(clients[i].pIdiLib->hLib);
        clients[i].pIdiLib = NULL;

        pmem = clients[i].pmem;
        clients[i].pmem = NULL;
      }

      clients[i].hDbg    = NULL;
      clients[i].request_pending = 0;
      if (clients[i].dma_handle >= 0) {
        /*
          Free DMA handle
          */
        diva_free_dma_descriptor (clients[i].request, clients[i].dma_handle);
        clients[i].dma_handle = -1;
      }
      clients[i].request = NULL;

      /*
        Log driver register, MAINT driver ID is '0'
        */
      len = sprintf (tmp, "DIMAINT - drv # %d = '%s' de-registered",
                     i, clients[i].Dbg.drvName);

      memset (&clients[i].Dbg, 0x00, sizeof(clients[i].Dbg));

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

      break;
    }
  }

  diva_os_leave_spin_lock (&dbg_q_lock, &old_irql, "read_ack");
  diva_os_leave_spin_lock (&dbg_adapter_lock, &old_irql1, "read_ack");

  if (pmem) {
    diva_os_free (0, pmem);
  }
}