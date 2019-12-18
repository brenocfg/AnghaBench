#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int uint; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ MMAL_DBG_ENTRY_T ;

/* Variables and functions */
#define  VCHIQ_BULK_RECEIVE_ABORTED 131 
#define  VCHIQ_BULK_RECEIVE_DONE 130 
#define  VCHIQ_BULK_TRANSMIT_ABORTED 129 
#define  VCHIQ_BULK_TRANSMIT_DONE 128 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static void on_bulk_ack(MMAL_DBG_ENTRY_T *entry,
                        char *buf,
                        size_t buflen)
{
   switch (entry->u.uint)
   {
   case VCHIQ_BULK_RECEIVE_ABORTED: snprintf(buf,buflen,"vchiq bulk rx abort"); break;
   case VCHIQ_BULK_TRANSMIT_ABORTED: snprintf(buf,buflen,"vchiq bulk tx abort"); break;
   case VCHIQ_BULK_TRANSMIT_DONE: snprintf(buf,buflen,"vchiq bulk tx done"); break;
   case VCHIQ_BULK_RECEIVE_DONE: snprintf(buf,buflen,"vchiq bulk rx done"); break;
   default: snprintf(buf,buflen,"vchiq unknown reason %d", entry->u.uint); break;
   }
}