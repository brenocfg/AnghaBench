#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_PARAMS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;
struct TYPE_2__ {int iters; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_PARAMS (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VCHIQ_BULK_MODE_BLOCKING ; 
 scalar_t__ VCHIQ_ERROR ; 
 int VCHIQ_MAKE_FOURCC (char,char,char,char) ; 
#define  VCHIQ_MAX_MSG_SIZE 128 
 scalar_t__ VCHIQ_SUCCESS ; 
 int VCHIQ_TEST_VER ; 
 int /*<<< orphan*/  clnt_callback ; 
 TYPE_1__ g_params ; 
 char* g_servname ; 
 scalar_t__ g_timeout_ms ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setup_auto_kill (scalar_t__) ; 
 int /*<<< orphan*/  vchiq_bulk_transmit (int /*<<< orphan*/ ,int**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_close_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_connect (int /*<<< orphan*/ ) ; 
 scalar_t__ vchiq_initialise (int /*<<< orphan*/ *) ; 
 scalar_t__ vchiq_open_service (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCHIQ_STATUS_T
vchiq_signal_test(void)
{
   /* Measure message round trip time for various sizes*/
   VCHIQ_INSTANCE_T vchiq_instance;
   VCHIQ_SERVICE_HANDLE_T vchiq_service;
   VCHIQ_SERVICE_PARAMS_T vchiq_service_params;
   int fourcc;

   static int sizes[] = { 0, 1024, 2048, VCHIQ_MAX_MSG_SIZE };

   fourcc = VCHIQ_MAKE_FOURCC(g_servname[0], g_servname[1], g_servname[2], g_servname[3]);

   printf("signal test - service:%s, iters:%d, version %d\n", g_servname, g_params.iters, VCHIQ_TEST_VER);

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

   INIT_PARAMS(&vchiq_service_params, fourcc, clnt_callback, "clnt userdata", VCHIQ_TEST_VER);
   if (vchiq_open_service(vchiq_instance, &vchiq_service_params, &vchiq_service) != VCHIQ_SUCCESS)
   {
      printf("* failed to open service - already in use?\n");
      return VCHIQ_ERROR;
   }

   vchiq_bulk_transmit(vchiq_service, &sizes, 16, 0, VCHIQ_BULK_MODE_BLOCKING);

   vchiq_close_service(vchiq_service);

   return VCHIQ_SUCCESS;
}