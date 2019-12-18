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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHI_CONNECTION_T ;
struct TYPE_6__ {int initialised; int num_connections; int /*<<< orphan*/ * open_handle; int /*<<< orphan*/  message_available_event; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/ * member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SERVICE_CREATION_T ;
typedef  int /*<<< orphan*/  GENCMD_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_FOURCC (char*) ; 
 int /*<<< orphan*/  VCHI_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  VC_FALSE ; 
 int /*<<< orphan*/  VC_GENCMD_VER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gencmd_callback ; 
 TYPE_3__ gencmd_client ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_gencmd_service () ; 
 scalar_t__ vchi_service_open (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_event_create (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 

void vc_vchi_gencmd_init (VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections )
{
   VCOS_STATUS_T status;
   int32_t success;
   int i;

   if (gencmd_client.initialised)
     return;

   // record the number of connections
   memset( &gencmd_client, 0, sizeof(GENCMD_SERVICE_T) );
   gencmd_client.num_connections = (int) num_connections;

   status = vcos_mutex_create(&gencmd_client.lock, "HGencmd");
   vcos_assert(status == VCOS_SUCCESS);
   status = vcos_event_create(&gencmd_client.message_available_event, "HGencmd");
   vcos_assert(status == VCOS_SUCCESS);

   for (i=0; i<gencmd_client.num_connections; i++) {

      // Create a 'LONG' service on the each of the connections
      SERVICE_CREATION_T gencmd_parameters = { VCHI_VERSION(VC_GENCMD_VER),
                                               MAKE_FOURCC("GCMD"),      // 4cc service code
                                               connections[i],           // passed in fn ptrs
                                               0,                        // tx fifo size (unused)
                                               0,                        // tx fifo size (unused)
                                               &gencmd_callback,         // service callback
                                               &gencmd_client.message_available_event, // callback parameter
                                               VC_FALSE,                 // want_unaligned_bulk_rx
                                               VC_FALSE,                 // want_unaligned_bulk_tx
                                               VC_FALSE                  // want_crc
                                               };

      success = vchi_service_open( initialise_instance, &gencmd_parameters, &gencmd_client.open_handle[i] );
      assert( success == 0 );
   }

   gencmd_client.initialised = 1;
   release_gencmd_service();
}