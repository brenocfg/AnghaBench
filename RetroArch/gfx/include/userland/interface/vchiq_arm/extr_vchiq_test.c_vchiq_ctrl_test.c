#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  service_params ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_7__ {char* userdata; void* version_min; void* version; int /*<<< orphan*/  callback; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_PARAMS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;
struct TYPE_8__ {int size; scalar_t__ data; } ;
typedef  TYPE_2__ VCHIQ_ELEMENT_T ;
struct TYPE_9__ {int blocksize; int iters; scalar_t__ echo; } ;

/* Variables and functions */
 int MSG_ECHO ; 
 int NUM_BULK_BUFS ; 
 scalar_t__ VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_MAKE_FOURCC (char,char,char,char) ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 void* VCHIQ_TEST_VER ; 
 scalar_t__* bulk_tx_data ; 
 int /*<<< orphan*/  clnt_callback ; 
 scalar_t__ ctrl_received ; 
 TYPE_6__ g_params ; 
 char* g_server_error ; 
 char* g_servname ; 
 int /*<<< orphan*/  g_shutdown ; 
 scalar_t__ g_timeout_ms ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setup_auto_kill (scalar_t__) ; 
 int /*<<< orphan*/  vchiq_connect (int /*<<< orphan*/ ) ; 
 scalar_t__ vchiq_initialise (int /*<<< orphan*/ *) ; 
 scalar_t__ vchiq_open_service (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vchiq_queue_message (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  vchiq_remove_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_event_wait (int /*<<< orphan*/ *) ; 
 int vcos_getmicrosecs () ; 
 int /*<<< orphan*/  vcos_log_trace (char*) ; 

__attribute__((used)) static VCHIQ_STATUS_T
vchiq_ctrl_test(void)
{
   VCHIQ_INSTANCE_T vchiq_instance;
   VCHIQ_SERVICE_HANDLE_T vchiq_service;
   VCHIQ_SERVICE_PARAMS_T service_params;
   uint32_t start, end;
   int i;

   ctrl_received = 0;
   if (g_params.blocksize < 4)
      g_params.blocksize = 4;

   for (i = 0; i < NUM_BULK_BUFS; i++)
   {
      int j;
      bulk_tx_data[i] = malloc(g_params.blocksize);
      if (!bulk_tx_data[i])
      {
         printf("* out of memory\n");
         return VCHIQ_ERROR;
      }
      *(int *)bulk_tx_data[i] = MSG_ECHO;
      for (j = 4; j < g_params.blocksize; j+=4)
      {
         *(unsigned int *)(bulk_tx_data[i] + j) = ((0x80 | i) << 24) + j;
      }
   }

#ifdef ANDROID
   if (g_timeout_ms)
   {
      setup_auto_kill(g_timeout_ms);
   }
#endif

   if (vchiq_initialise(&vchiq_instance) != VCHIQ_SUCCESS)
   {
      printf("* failed to open vchiq instance\n");
      return VCHIQ_ERROR;
   }

   vchiq_connect(vchiq_instance);

   memset(&service_params, 0, sizeof(service_params));

   service_params.fourcc = VCHIQ_MAKE_FOURCC(g_servname[0], g_servname[1], g_servname[2], g_servname[3]);
   service_params.callback = clnt_callback;
   service_params.userdata = "clnt userdata";
   service_params.version = VCHIQ_TEST_VER;
   service_params.version_min = VCHIQ_TEST_VER;

   if (vchiq_open_service(vchiq_instance, &service_params, &vchiq_service) != VCHIQ_SUCCESS)
   {
      printf("* failed to open service - already in use?\n");
      return VCHIQ_ERROR;
   }

   printf("Ctrl test - service:%s, block size:%d, iters:%d\n", g_servname, g_params.blocksize, g_params.iters);

   start = vcos_getmicrosecs();

   for (i = 0; i < g_params.iters; i++)
   {
      VCHIQ_ELEMENT_T element;
      element.data = bulk_tx_data[i % NUM_BULK_BUFS];
      element.size = g_params.blocksize;

      if (vchiq_queue_message(vchiq_service, &element, 1) != VCHIQ_SUCCESS)
      {
         printf("* failed to send a message\n");
         goto error_exit;
      }
      if (g_server_error)
      {
         printf("* error - %s\n", g_server_error);
         goto error_exit;
      }
   }

   vcos_log_trace("Sent all messages");

   if (g_params.echo)
   {
      vcos_log_trace("vchiq_test: waiting for shutdown");

      vcos_event_wait(&g_shutdown);
   }

   if (g_server_error)
   {
      printf("* error - %s\n", g_server_error);
      goto error_exit;
   }

   end = vcos_getmicrosecs();

   vchiq_remove_service(vchiq_service);

   vcos_log_trace("vchiq_test: shutting down");

   vchiq_shutdown(vchiq_instance);

   printf("Elapsed time: %dus per iteration\n", (end - start) / g_params.iters);

   return VCHIQ_SUCCESS;

error_exit:
   vchiq_remove_service(vchiq_service);
   vchiq_shutdown(vchiq_instance);
   return VCHIQ_ERROR;
}