#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* entries; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_type; int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  MMAL_DBG_EVENT_TYPE_T ;
typedef  TYPE_1__ MMAL_DBG_ENTRY_T ;

/* Variables and functions */
 int MMAL_DBG_ENTRIES_MASK ; 
 int /*<<< orphan*/  mmal_dbg_lock ; 
 TYPE_3__* mmal_dbg_log ; 
 int /*<<< orphan*/  vcos_getmicrosecs () ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline MMAL_DBG_ENTRY_T *mmal_log_lock_event(MMAL_DBG_EVENT_TYPE_T event_type ) {
   uint32_t index;
   MMAL_DBG_ENTRY_T *entry;
   vcos_mutex_lock(&mmal_dbg_lock);
   index = mmal_dbg_log->index++;
   entry = mmal_dbg_log->entries + (index & MMAL_DBG_ENTRIES_MASK);
   entry->time = vcos_getmicrosecs();
   entry->event_type = event_type;
   return entry;
}