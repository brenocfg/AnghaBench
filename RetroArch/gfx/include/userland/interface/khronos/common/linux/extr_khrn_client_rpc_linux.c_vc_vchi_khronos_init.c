#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCOS_STATUS_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_3__ {int /*<<< orphan*/  callback; int /*<<< orphan*/  fourcc; void* version_min; void* version; int /*<<< orphan*/ * userdata; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_PARAMS_T ;

/* Variables and functions */
 int /*<<< orphan*/  FOURCC_KHAN ; 
 int /*<<< orphan*/  FOURCC_KHHN ; 
 int /*<<< orphan*/  FOURCC_KHRN ; 
 int /*<<< orphan*/  UNUSED_NDEBUG (scalar_t__) ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ VCOS_SUCCESS ; 
 void* VC_KHRN_VERSION ; 
 int /*<<< orphan*/  bulk_event ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  khan_callback ; 
 int /*<<< orphan*/  khhn_callback ; 
 int /*<<< orphan*/  khhn_queue ; 
 int /*<<< orphan*/  khrn_callback ; 
 int /*<<< orphan*/  khrn_queue ; 
 int /*<<< orphan*/  khrn_vchiq_instance ; 
 scalar_t__ vchiq_connect (int /*<<< orphan*/ ) ; 
 scalar_t__ vchiq_initialise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_khan_service ; 
 int /*<<< orphan*/  vchiq_khhn_service ; 
 int /*<<< orphan*/  vchiq_khrn_service ; 
 scalar_t__ vchiq_open_service (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiu_queue_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_event_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_error (char*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*) ; 

void vc_vchi_khronos_init()
{
   VCOS_STATUS_T status = vcos_event_create(&bulk_event, NULL);
   UNUSED_NDEBUG(status);
   vcos_assert(status == VCOS_SUCCESS);

   if (vchiq_initialise(&khrn_vchiq_instance) != VCHIQ_SUCCESS)
   {
      vcos_log_error("* failed to open vchiq device");

      exit(1);
   }

   vcos_log_trace("gldemo: connecting");

   if (vchiq_connect(khrn_vchiq_instance) != VCHIQ_SUCCESS)
   {
      vcos_log_error("* failed to connect");

      exit(1);
   }

   VCHIQ_STATUS_T khan_return, khrn_return, khhn_return;
   VCHIQ_SERVICE_PARAMS_T params;

   params.userdata = NULL;
   params.version = VC_KHRN_VERSION;
   params.version_min = VC_KHRN_VERSION;

   params.fourcc = FOURCC_KHAN;
   params.callback = khan_callback;
   khan_return = vchiq_open_service(khrn_vchiq_instance, &params, &vchiq_khan_service);

   params.fourcc = FOURCC_KHRN;
   params.callback = khrn_callback;
   khrn_return = vchiq_open_service(khrn_vchiq_instance, &params, &vchiq_khrn_service);

   params.fourcc = FOURCC_KHHN;
   params.callback = khhn_callback;
   khhn_return = vchiq_open_service(khrn_vchiq_instance, &params, &vchiq_khhn_service);

   if (khan_return != VCHIQ_SUCCESS ||
       khrn_return != VCHIQ_SUCCESS ||
       khhn_return != VCHIQ_SUCCESS)
   {
      vcos_log_error("* failed to add service - already in use?");

      exit(1);
   }
   vchiu_queue_init(&khrn_queue, 64);
   vchiu_queue_init(&khhn_queue, 64);

   vcos_log_trace("gldemo: connected");

   /*
      attach to process (there's just one)
   */

//   bool success = client_process_attach();
//   vcos_assert(success);
}