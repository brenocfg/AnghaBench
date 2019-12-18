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
typedef  int /*<<< orphan*/  VCOS_THREAD_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_2__ {int align_size; int iters; scalar_t__ verify; void* server_message_quota; void* client_message_quota; void* blocksize; void* server_align; void* client_align; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_ERROR ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int VCOS_AFFINITY_CPU1 ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 int /*<<< orphan*/  VCOS_LOG_INFO ; 
 int /*<<< orphan*/  VCOS_LOG_TRACE ; 
 int /*<<< orphan*/  VCOS_START ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  check_timer () ; 
 int /*<<< orphan*/  exit (int) ; 
 void* func_data_test_end ; 
 void* func_data_test_start ; 
 int /*<<< orphan*/  g_mutex ; 
 TYPE_1__ g_params ; 
 int /*<<< orphan*/  g_server_reply ; 
 char* g_servname ; 
 int /*<<< orphan*/  g_shutdown ; 
 void* g_timeout_ms ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  reserve_test (int,int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ vchiq_bulk_test () ; 
 scalar_t__ vchiq_ctrl_test () ; 
 scalar_t__ vchiq_functional_test () ; 
 scalar_t__ vchiq_ping_test () ; 
 scalar_t__ vchiq_signal_test () ; 
 int /*<<< orphan*/  vchiq_test_server ; 
 int /*<<< orphan*/  vcos_demand (void*) ; 
 int /*<<< orphan*/  vcos_event_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_thread_create_classic (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*,void*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ want_echo ; 

__attribute__((used)) static int vchiq_test(int argc, char **argv)
{
   VCHIQ_STATUS_T status;
   int run_bulk_test = 0;
   int run_ctrl_test = 0;
   int run_functional_test = 0;
   int run_ping_test = 0;
   int run_signal_test = 0;
   int verbose = 0;
   int argn;

   argn = 1;
   while ((argn < argc) && (argv[argn][0] == '-'))
   {
      const char *arg = argv[argn++];
      if (strcmp(arg, "-s") == 0)
      {
         g_servname = argv[argn++];
         if (!g_servname || (strlen(g_servname) != 4))
         {
            usage();
         }
      }
      else if (strcasecmp(arg, "-a") == 0)
      {
         g_params.align_size = (strcmp(arg, "-A") == 0) ? 4096 : 32;
         g_params.client_align = atoi(argv[argn++]);
         g_params.server_align = atoi(argv[argn++]);
      }
      else if (strcmp(arg, "-b") == 0)
      {
         run_bulk_test = 1;
         g_params.blocksize = atoi(argv[argn++]);
      }
      else if (strcmp(arg, "-c") == 0)
      {
         run_ctrl_test = 1;
         g_params.blocksize = atoi(argv[argn++]);
      }
      else if (strcmp(arg, "-e") == 0)
      {
         want_echo = 0;
      }
      else if (strcmp(arg, "-f") == 0)
      {
         run_functional_test = 1;
      }
      else if (strcmp(arg, "-h") == 0)
      {
         usage();
      }
      else if (strcmp(arg, "-i") == 0)
      {
         run_signal_test = 1;
      }
      else if (strcmp(arg, "-m") == 0)
      {
         g_params.client_message_quota = atoi(argv[argn++]);
      }
      else if (strcmp(arg, "-M") == 0)
      {
         g_params.server_message_quota = atoi(argv[argn++]);
      }
      else if (strcmp(arg, "-p") == 0)
      {
         run_ping_test = 1;
         g_params.iters = 1000;
      }
      else if (strcmp(arg, "-q") == 0)
      {
         /* coverity[missing_lock : FALSE] - g_server_reply is not used for mutual exclusion */
         g_params.verify = 0;
      }
#ifdef __linux__
      else if (strcmp(arg, "-r") == 0)
      {
         int reserve, delay;
         if (argn+1 < argc)
         {
            reserve = atoi(argv[argn++]);
            delay = atoi(argv[argn++]);
            reserve_test(reserve, delay);
            exit(0);
         }
         else
         {
            printf("not enough arguments (-r reserve delay)\n");
            exit(-1);
         }
      }
#endif
#ifdef ANDROID
      else if (strcmp(arg, "-K") == 0)
      {
         if (argn < argc)
            g_timeout_ms = atoi(argv[argn++]);
         else
         {
            printf("not enough arguments (-K timeout)\n");
            exit(-1);
         }
      }
#endif
      else if (strcmp(arg, "-t") == 0)
      {
         check_timer();
         exit(0);
      }
      else if (strcmp(arg, "-v") == 0)
      {
         verbose = 1;
      }
      else if (strcmp(arg, "-S") == 0)
      {
         func_data_test_start = atoi(argv[argn++]);
      }
      else if (strcmp(arg, "-E") == 0)
      {
         func_data_test_end = atoi(argv[argn++]);
      }
      else
      {
         printf("* unknown option '%s'\n", arg);
         usage();
      }
   }

   if ((run_ctrl_test + run_bulk_test + run_functional_test + run_ping_test + run_signal_test) != 1)
      usage();

   if (argn < argc)
   {
      g_params.iters = atoi(argv[argn++]);
      if (argn != argc)
      {
         usage();
      }
   }

   vcos_log_set_level(VCOS_LOG_CATEGORY, verbose ? VCOS_LOG_TRACE : VCOS_LOG_INFO);
   vcos_log_register("vchiq_test", VCOS_LOG_CATEGORY);

#ifdef VCHIQ_LOCAL
   {
      static VCOS_THREAD_T server_task;
      void          *pointer = NULL;
      int stack_size = 4096;

#if VCOS_CAN_SET_STACK_ADDR
      pointer = malloc(stack_size);
      vcos_demand(pointer);
#endif
      vcos_thread_create_classic(&server_task, "vchiq_test server", vchiq_test_server, (void *)0, pointer, stack_size,
                                 10 | VCOS_AFFINITY_CPU1, 20, VCOS_START);
   }
#endif

   vcos_event_create(&g_server_reply, "g_server_reply");
   vcos_event_create(&g_shutdown, "g_shutdown");
   vcos_mutex_create(&g_mutex, "g_mutex");

   status = VCHIQ_ERROR;

   if (run_bulk_test)
      status = vchiq_bulk_test();
   else if (run_ctrl_test)
      status = vchiq_ctrl_test();
   else if (run_functional_test)
      status = vchiq_functional_test();
   else if (run_ping_test)
      status = vchiq_ping_test();
   else if (run_signal_test)
      status = vchiq_signal_test();

   return (status == VCHIQ_SUCCESS) ? 0 : -1;
}