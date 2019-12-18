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
typedef  size_t uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  VCOS_THREAD_ATTR_T ;
typedef  scalar_t__ VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHI_CONNECTION_T ;
struct TYPE_6__ {int initialised; size_t num_connections; int /*<<< orphan*/ * notify_handle; int /*<<< orphan*/ * client_handle; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/ * member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SERVICE_CREATION_T ;
typedef  int /*<<< orphan*/  DISPMANX_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  DISPMANX_CLIENT_NAME ; 
 int /*<<< orphan*/  DISPMANX_NOTIFY_NAME ; 
 int /*<<< orphan*/  VCHI_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  VC_DISPMANX_VERSION ; 
 int /*<<< orphan*/  VC_FALSE ; 
 TYPE_3__ dispmanx_client ; 
 int /*<<< orphan*/  dispmanx_client_callback ; 
 int /*<<< orphan*/  dispmanx_message_available_event ; 
 int /*<<< orphan*/  dispmanx_notify_available_event ; 
 int /*<<< orphan*/  dispmanx_notify_callback ; 
 int /*<<< orphan*/  dispmanx_notify_func ; 
 int /*<<< orphan*/  dispmanx_notify_task ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vchi_service_open (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_event_create (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_thread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_attr_setstacksize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vcos_thread_attr_settimeslice (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vcos_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vc_vchi_dispmanx_init (VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections ) {
   VCOS_STATUS_T status;
   int32_t success;
   uint32_t i;

   if (dispmanx_client.initialised)
     return;

   // record the number of connections
   memset( &dispmanx_client, 0, sizeof(DISPMANX_SERVICE_T) );
   dispmanx_client.num_connections = num_connections;

   status = vcos_mutex_create(&dispmanx_client.lock, "HDispmanx");
   vcos_assert(status == VCOS_SUCCESS);

   status = vcos_event_create(&dispmanx_message_available_event, "HDispmanx");
   vcos_assert(status == VCOS_SUCCESS);

   status = vcos_event_create(&dispmanx_notify_available_event, "HDispmanx");
   vcos_assert(status == VCOS_SUCCESS);

   dispmanx_client.initialised = 1;

   for (i=0; i<dispmanx_client.num_connections; i++) {

      VCOS_THREAD_ATTR_T attrs;

      // Create a 'Client' service on the each of the connections
      SERVICE_CREATION_T dispmanx_parameters = { VCHI_VERSION(VC_DISPMANX_VERSION),
                                                 DISPMANX_CLIENT_NAME,     // 4cc service code
                                                 connections[i],           // passed in fn ptrs
                                                 0,                        // tx fifo size (unused)
                                                 0,                        // tx fifo size (unused)
                                                 &dispmanx_client_callback, // service callback
                                                 &dispmanx_message_available_event,  // callback parameter
                                                 VC_FALSE,                  // want_unaligned_bulk_rx
                                                 VC_FALSE,                  // want_unaligned_bulk_tx
                                                 VC_FALSE,                  // want_crc
                                                 };

      SERVICE_CREATION_T dispmanx_parameters2 = { VCHI_VERSION(VC_DISPMANX_VERSION),
                                                  DISPMANX_NOTIFY_NAME,   // 4cc service code
                                                  connections[i],           // passed in fn ptrs
                                                  0,                        // tx fifo size (unused)
                                                  0,                        // tx fifo size (unused)
                                                  &dispmanx_notify_callback, // service callback
                                                  &dispmanx_notify_available_event,  // callback parameter
                                                  VC_FALSE,                  // want_unaligned_bulk_rx
                                                  VC_FALSE,                  // want_unaligned_bulk_tx
                                                  VC_FALSE,                  // want_crc
                                                   };

      success = vchi_service_open( initialise_instance, &dispmanx_parameters, &dispmanx_client.client_handle[i] );
      vcos_assert( success == 0 );

      // Create the async service of dispman to handle update callback

      success = vchi_service_open( initialise_instance, &dispmanx_parameters2, &dispmanx_client.notify_handle[i] );
      vcos_assert( success == 0 );

      //Create the notifier task
      vcos_thread_attr_init(&attrs);
      vcos_thread_attr_setstacksize(&attrs, 2048);
      vcos_thread_attr_settimeslice(&attrs, 1);

      status = vcos_thread_create(&dispmanx_notify_task, "HDispmanx Notify", &attrs, dispmanx_notify_func, NULL);
      vcos_assert(status == VCOS_SUCCESS);

      // release services until they're actually used
      vchi_service_release(dispmanx_client.client_handle[i]);
      vchi_service_release(dispmanx_client.notify_handle[i]);
   }
}