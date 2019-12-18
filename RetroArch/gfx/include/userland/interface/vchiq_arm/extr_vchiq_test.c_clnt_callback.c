#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  scalar_t__ VCHIQ_REASON_T ;
struct TYPE_5__ {size_t size; char* data; } ;
typedef  TYPE_1__ VCHIQ_HEADER_T ;
struct TYPE_6__ {size_t iters; scalar_t__ echo; int /*<<< orphan*/  blocksize; scalar_t__ verify; } ;

/* Variables and functions */
 int MSG_ECHO ; 
 size_t NUM_BULK_BUFS ; 
 scalar_t__ VCHIQ_BULK_RECEIVE_ABORTED ; 
 scalar_t__ VCHIQ_BULK_RECEIVE_DONE ; 
 scalar_t__ VCHIQ_BULK_TRANSMIT_ABORTED ; 
 scalar_t__ VCHIQ_BULK_TRANSMIT_DONE ; 
 scalar_t__ VCHIQ_MESSAGE_AVAILABLE ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VCOS_BKPT ; 
 char** bulk_rx_data ; 
 int bulk_rx_received ; 
 size_t bulk_rx_sent ; 
 char** bulk_tx_data ; 
 int bulk_tx_received ; 
 size_t bulk_tx_sent ; 
 size_t ctrl_received ; 
 int /*<<< orphan*/  g_mutex ; 
 TYPE_3__ g_params ; 
 char* g_server_error ; 
 int /*<<< orphan*/  g_server_reply ; 
 int /*<<< orphan*/  g_shutdown ; 
 scalar_t__ mem_check (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_queue_bulk_receive (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vchiq_queue_bulk_transmit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_info (char*,int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int,...) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCHIQ_STATUS_T
clnt_callback(VCHIQ_REASON_T reason, VCHIQ_HEADER_T *header,
   VCHIQ_SERVICE_HANDLE_T service, void *bulk_userdata)
{
   int data;
   vcos_mutex_lock(&g_mutex);
   if (reason == VCHIQ_MESSAGE_AVAILABLE)
   {
      /*
       * Store the header size as it is going to be released
       * and the size may be overwritten by the release.
       */
      size_t header_size = header->size;

      if (header_size <= 1)
         vchiq_release_message(service, header);
      else
      /* Responses of length 0 are not sync points */
      if ((header_size >= 4) && (memcpy(&data, header->data, sizeof(data)), data == MSG_ECHO))
      {
         /* This is a complete echoed packet */
         if (g_params.verify && (mem_check(header->data, bulk_tx_data[ctrl_received % NUM_BULK_BUFS], g_params.blocksize) != 0))
            g_server_error = "corrupt data";
         else
            ctrl_received++;
         if (g_server_error || (ctrl_received == g_params.iters))
            vcos_event_signal(&g_shutdown);
         vchiq_release_message(service, header);
      }
      else if (header_size != 0)
         g_server_error = header->data;

      if ((header_size != 0) || g_server_error)
         vcos_event_signal(&g_server_reply);
   }
   else if (reason == VCHIQ_BULK_TRANSMIT_DONE)
   {
      int i = (int)bulk_userdata;
      vcos_log_trace("  BULK_TRANSMIT_DONE(%d)", i);
      if (bulk_tx_received < 0)
         vcos_event_signal(&g_server_reply);
      else
      {
         vcos_assert(i == bulk_tx_received);
         bulk_tx_received++;
         if (bulk_tx_sent < g_params.iters)
         {
            vchiq_queue_bulk_transmit(service, bulk_tx_data[i % NUM_BULK_BUFS], g_params.blocksize, (void *)bulk_tx_sent);
            bulk_tx_sent++;
         }
      }
   }
   else if (reason == VCHIQ_BULK_RECEIVE_DONE)
   {
      int i = (int)bulk_userdata;
      vcos_log_trace("  BULK_RECEIVE_DONE(%d): data '%s'", i, bulk_rx_data[i % NUM_BULK_BUFS]);
      vcos_assert(i == bulk_rx_received);
      if (g_params.verify && (mem_check(bulk_tx_data[i % NUM_BULK_BUFS], bulk_rx_data[i % NUM_BULK_BUFS], g_params.blocksize) != 0))
      {
         vcos_log_error("* Data corruption - %d: %x, %x, %x", i, (unsigned int)bulk_tx_data[i % NUM_BULK_BUFS], (unsigned int)bulk_rx_data[i % NUM_BULK_BUFS], g_params.blocksize);
         VCOS_BKPT;
      }
      bulk_rx_received++;
      if (bulk_rx_sent < g_params.iters)
      {
         if (g_params.verify)
            memset(bulk_rx_data[i % NUM_BULK_BUFS], 0xff, g_params.blocksize);
         vchiq_queue_bulk_receive(service, bulk_rx_data[i % NUM_BULK_BUFS], g_params.blocksize, (void *)bulk_rx_sent);
         bulk_rx_sent++;
      }
   }
   else if (reason == VCHIQ_BULK_TRANSMIT_ABORTED)
   {
      int i = (int)bulk_userdata;
      vcos_log_info("  BULK_TRANSMIT_ABORTED(%d)", i);
   }
   else if (reason == VCHIQ_BULK_RECEIVE_ABORTED)
   {
      int i = (int)bulk_userdata;
      vcos_log_info("  BULK_RECEIVE_ABORTED(%d)", i);
   }
   if ((bulk_tx_received == g_params.iters) &&
      ((g_params.echo == 0) || (bulk_rx_received == g_params.iters)))
      vcos_event_signal(&g_shutdown);
   vcos_mutex_unlock(&g_mutex);
   return VCHIQ_SUCCESS;
}