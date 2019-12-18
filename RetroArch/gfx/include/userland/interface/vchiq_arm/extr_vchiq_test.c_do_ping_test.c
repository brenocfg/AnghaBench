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
typedef  scalar_t__ uint32_t ;
struct test_params {int blocksize; int iters; scalar_t__ echo; scalar_t__ verify; void* magic; int /*<<< orphan*/  client_message_quota; } ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
struct TYPE_3__ {char* data; int size; } ;
typedef  TYPE_1__ VCHIQ_ELEMENT_T ;

/* Variables and functions */
 void* MSG_ASYNC ; 
 void* MSG_CONFIG ; 
 void* MSG_ONEWAY ; 
 void* MSG_SYNC ; 
 int /*<<< orphan*/  VCHIQ_BULK_MODE_BLOCKING ; 
 int /*<<< orphan*/  VCHIQ_BULK_MODE_NOCALLBACK ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_OPTION_MESSAGE_QUOTA ; 
 int bulk_tx_received ; 
 int /*<<< orphan*/  free (char*) ; 
 struct test_params g_params ; 
 int /*<<< orphan*/  g_server_reply ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int /*<<< orphan*/  vchiq_bulk_transmit (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_queue_bulk_transmit (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_queue_message (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vchiq_set_service_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_event_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_getmicrosecs () ; 
 int vcos_max (int,int) ; 
 int /*<<< orphan*/  vcos_sleep (int) ; 

__attribute__((used)) static void
do_ping_test(VCHIQ_SERVICE_HANDLE_T service, int size, int async, int oneway, int iters)
{
   uint32_t start, end;
   char *ping_buf = malloc(size + sizeof(struct test_params));
   struct test_params *params = (struct test_params *)ping_buf;
   VCHIQ_ELEMENT_T element;
   int i;

   element.data = ping_buf;

   /* Set up the quotas for messages */
   *params = g_params;
   params->magic = MSG_CONFIG;
   params->blocksize = 0;
   element.size = sizeof(*params);
   vchiq_queue_message(service, &element, 1);
   vcos_event_wait(&g_server_reply);
   vchiq_set_service_option(service, VCHIQ_SERVICE_OPTION_MESSAGE_QUOTA, params->client_message_quota);

   /* Allow enough room for the type header */
   element.size = (size < 4) ? 4 : size;

   bulk_tx_received = -1;

   start = vcos_getmicrosecs();
   for (i = 0; i < iters; i++)
   {
      int j;
      for (j = 0; j < vcos_max(async, oneway); j++)
      {
         if (j < async)
         {
            params->magic = MSG_ASYNC;
            vchiq_queue_message(service, &element, 1);
         }
         if (j < oneway)
         {
            params->magic = MSG_ONEWAY;
            vchiq_queue_message(service, &element, 1);
         }
      }
      params->magic = MSG_SYNC;
      vchiq_queue_message(service, &element, 1);
      vcos_event_wait(&g_server_reply);
   }
   end = vcos_getmicrosecs();

   printf("ping (size %d, %d async, %d oneway) -> %fus\n", size, async, oneway, ((float)(end - start))/iters);

   vcos_sleep(20);

   if ((async == 0) && (oneway == 0))
   {
      *params = g_params;
      params->magic = MSG_CONFIG;
      params->blocksize = size ? size : 8;
      params->iters = iters;
      params->verify = 0;
      params->echo = 0;

      element.size = sizeof(*params);
      vchiq_queue_message(service, &element, 1);
      vcos_event_wait(&g_server_reply);

      vcos_sleep(30);

      start = vcos_getmicrosecs();
      for (i = 0; i < iters; i++)
      {
         vchiq_queue_bulk_transmit(service, ping_buf, params->blocksize, 0);
         vcos_event_wait(&g_server_reply);
      }
      end = vcos_getmicrosecs();

      printf("bulk (size %d, async) -> %fus\n", size, ((float)(end - start))/iters);

      vcos_sleep(40);
   }

   if (oneway == 0)
   {
      *params = g_params;
      params->magic = MSG_CONFIG;
      params->blocksize = size ? size : 8;
      params->iters = iters * (async + 1);
      params->verify = 0;
      params->echo = 0;

      element.size = sizeof(*params);
      vchiq_queue_message(service, &element, 1);
      vcos_event_wait(&g_server_reply);

      vcos_sleep(50);

      start = vcos_getmicrosecs();
      for (i = 0; i < iters; i++)
      {
         int j;
         for (j = 0; j < async; j++)
            vchiq_bulk_transmit(service, ping_buf, params->blocksize, 0, VCHIQ_BULK_MODE_NOCALLBACK);
         vchiq_bulk_transmit(service, ping_buf, params->blocksize, 0, VCHIQ_BULK_MODE_BLOCKING);
      }
      end = vcos_getmicrosecs();

      printf("bulk (size %d, %d async) -> %fus\n", size, async, ((float)(end - start))/iters);

      vcos_sleep(60);
   }

   free(ping_buf);

   bulk_tx_received = 0;
}