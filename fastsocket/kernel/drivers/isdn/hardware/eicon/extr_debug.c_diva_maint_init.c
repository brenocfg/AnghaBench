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
typedef  int dword ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  MSG_QUEUE ;

/* Variables and functions */
 scalar_t__ DBG_MAGIC ; 
 scalar_t__* TraceFilter ; 
 int TraceFilterChannel ; 
 int TraceFilterIdent ; 
 int /*<<< orphan*/  dbg_adapter_lock ; 
 int /*<<< orphan*/ * dbg_base ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/ * dbg_queue ; 
 int /*<<< orphan*/  diva_os_destroy_spin_lock (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_get_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ diva_os_initialize_spin_lock (int /*<<< orphan*/ *,char*) ; 
 int external_dbg_queue ; 
 int /*<<< orphan*/  queueInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_sec ; 
 int /*<<< orphan*/  start_usec ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

int diva_maint_init (byte* base, unsigned long length, int do_init) {
  if (dbg_queue || (!base) || (length < (4096*4))) {
    return (-1);
  }

  TraceFilter[0]     =  0;
  TraceFilterIdent   = -1;
  TraceFilterChannel = -1;

  dbg_base = base;

  diva_os_get_time (&start_sec, &start_usec);

  *(dword*)base  = (dword)DBG_MAGIC; /* Store Magic */
  base   += sizeof(dword);
  length -= sizeof(dword);

  *(dword*)base = 2048; /* Extension Field Length */
  base   += sizeof(dword);
  length -= sizeof(dword);

  strcpy (base, "KERNEL MODE BUFFER\n");
  base   += 2048;
  length -= 2048;

  *(dword*)base = 0; /* Terminate extension */
  base   += sizeof(dword);
  length -= sizeof(dword);

  *(void**)base  =  (void*)(base+sizeof(void*)); /* Store Base  */
  base   += sizeof(void*);
  length -= sizeof(void*);

  dbg_queue = (MSG_QUEUE*)base;
  queueInit (dbg_queue, base + sizeof(MSG_QUEUE), length - sizeof(MSG_QUEUE) - 512);
  external_dbg_queue = 0;

  if (!do_init) {
    external_dbg_queue = 1; /* memory was located on the external device */
  }


	if (diva_os_initialize_spin_lock (&dbg_q_lock, "dbg_init")) {
    dbg_queue = NULL;
    dbg_base = NULL;
    external_dbg_queue = 0;
		return (-1);
  }

	if (diva_os_initialize_spin_lock (&dbg_adapter_lock, "dbg_init")) {
    diva_os_destroy_spin_lock(&dbg_q_lock, "dbg_init");
    dbg_queue = NULL;
    dbg_base = NULL;
    external_dbg_queue = 0;
		return (-1);
  }

  return (0);
}