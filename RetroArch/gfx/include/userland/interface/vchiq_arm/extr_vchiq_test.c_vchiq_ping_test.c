#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sizes ;
typedef  int /*<<< orphan*/  service_params ;
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_PARAMS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  scalar_t__ VCHIQ_INSTANCE_T ;
struct TYPE_8__ {int iters; } ;
struct TYPE_6__ {int version; int version_min; } ;
struct TYPE_7__ {int service_id; int /*<<< orphan*/ * callback_param; int /*<<< orphan*/  callback; TYPE_1__ version; } ;
typedef  TYPE_2__ SERVICE_CREATION_T ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_PARAMS (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ VCHIQ_ERROR ; 
 int VCHIQ_MAKE_FOURCC (char,char,char,char) ; 
#define  VCHIQ_MAX_MSG_SIZE 128 
 scalar_t__ VCHIQ_SUCCESS ; 
 int VCHIQ_TEST_VER ; 
 int /*<<< orphan*/  clnt_callback ; 
 int /*<<< orphan*/  do_ping_test (int /*<<< orphan*/ ,int,int,int,int const) ; 
 int /*<<< orphan*/  do_vchi_ping_test (int /*<<< orphan*/ ,int,int,int,int const) ; 
 TYPE_5__ g_params ; 
 char* g_servname ; 
 scalar_t__ g_timeout_ms ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setup_auto_kill (scalar_t__) ; 
 int /*<<< orphan*/  vchi_clnt_callback ; 
 int /*<<< orphan*/  vchi_service_close (int /*<<< orphan*/ ) ; 
 scalar_t__ vchi_service_open (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_close_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_connect (scalar_t__) ; 
 scalar_t__ vchiq_initialise (scalar_t__*) ; 
 scalar_t__ vchiq_open_service (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCHIQ_STATUS_T
vchiq_ping_test(void)
{
   /* Measure message round trip time for various sizes*/
   VCHIQ_INSTANCE_T vchiq_instance;
   VCHIQ_SERVICE_HANDLE_T vchiq_service;
   VCHI_SERVICE_HANDLE_T vchi_service;
   SERVICE_CREATION_T service_params;
   VCHIQ_SERVICE_PARAMS_T vchiq_service_params;
   int fourcc;

   static int sizes[] = { 0, 1024, 2048, VCHIQ_MAX_MSG_SIZE };
   unsigned int i;

   fourcc = VCHIQ_MAKE_FOURCC(g_servname[0], g_servname[1], g_servname[2], g_servname[3]);

   printf("Ping test - service:%s, iters:%d, version %d\n", g_servname, g_params.iters, VCHIQ_TEST_VER);

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
   service_params.version.version = service_params.version.version_min = VCHIQ_TEST_VER;
   service_params.service_id = fourcc;
   service_params.callback = vchi_clnt_callback;
   service_params.callback_param = &vchi_service;

   if (vchi_service_open((VCHI_INSTANCE_T)vchiq_instance, &service_params, &vchi_service) != VCHIQ_SUCCESS)
   {
      printf("* failed to open service - already in use?\n");
      return VCHIQ_ERROR;
   }

   for (i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++)
   {
      const int iter_count = g_params.iters;
      do_vchi_ping_test(vchi_service, sizes[i], 0, 0, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 0, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 1, 0, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 2, 0, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 10, 0, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 1, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 2, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 10, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 10, 10, iter_count);
      do_vchi_ping_test(vchi_service, sizes[i], 100, 0, iter_count/10);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 100, iter_count/10);
      do_vchi_ping_test(vchi_service, sizes[i], 100, 100, iter_count/10);
      do_vchi_ping_test(vchi_service, sizes[i], 200, 0, iter_count/10);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 200, iter_count/10);
      do_vchi_ping_test(vchi_service, sizes[i], 200, 200, iter_count/10);
      do_vchi_ping_test(vchi_service, sizes[i], 400, 0, iter_count/20);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 400, iter_count/20);
      do_vchi_ping_test(vchi_service, sizes[i], 400, 400, iter_count/20);
      do_vchi_ping_test(vchi_service, sizes[i], 1000, 0, iter_count/50);
      do_vchi_ping_test(vchi_service, sizes[i], 0, 1000, iter_count/50);
      do_vchi_ping_test(vchi_service, sizes[i], 1000, 1000, iter_count/50);
   }

   vchi_service_close(vchi_service);

   INIT_PARAMS(&vchiq_service_params, fourcc, clnt_callback, "clnt userdata", VCHIQ_TEST_VER);
   if (vchiq_open_service(vchiq_instance, &vchiq_service_params, &vchiq_service) != VCHIQ_SUCCESS)
   {
      printf("* failed to open service - already in use?\n");
      return VCHIQ_ERROR;
   }

   for (i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++)
   {
      const int iter_count = g_params.iters;
      do_ping_test(vchiq_service, sizes[i], 0, 0, iter_count);
      do_ping_test(vchiq_service, sizes[i], 0, 0, iter_count);
      do_ping_test(vchiq_service, sizes[i], 1, 0, iter_count);
      do_ping_test(vchiq_service, sizes[i], 2, 0, iter_count);
      do_ping_test(vchiq_service, sizes[i], 10, 0, iter_count);
      do_ping_test(vchiq_service, sizes[i], 0, 1, iter_count);
      do_ping_test(vchiq_service, sizes[i], 0, 2, iter_count);
      do_ping_test(vchiq_service, sizes[i], 0, 10, iter_count);
      do_ping_test(vchiq_service, sizes[i], 10, 10, iter_count);
      do_ping_test(vchiq_service, sizes[i], 100, 0, iter_count/10);
      do_ping_test(vchiq_service, sizes[i], 0, 100, iter_count/10);
      do_ping_test(vchiq_service, sizes[i], 100, 100, iter_count/10);
      do_ping_test(vchiq_service, sizes[i], 200, 0, iter_count/10);
      do_ping_test(vchiq_service, sizes[i], 0, 200, iter_count/10);
      do_ping_test(vchiq_service, sizes[i], 200, 200, iter_count/10);
      do_ping_test(vchiq_service, sizes[i], 400, 0, iter_count/20);
      do_ping_test(vchiq_service, sizes[i], 0, 400, iter_count/20);
      do_ping_test(vchiq_service, sizes[i], 400, 400, iter_count/20);
      do_ping_test(vchiq_service, sizes[i], 1000, 0, iter_count/50);
      do_ping_test(vchiq_service, sizes[i], 0, 1000, iter_count/50);
      do_ping_test(vchiq_service, sizes[i], 1000, 1000, iter_count/50);
   }

   vchiq_close_service(vchiq_service);

   return VCHIQ_SUCCESS;
}