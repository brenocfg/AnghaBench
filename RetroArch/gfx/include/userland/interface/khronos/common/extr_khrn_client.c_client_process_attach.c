#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ KHR_STATUS_T ;

/* Variables and functions */
 scalar_t__ KHR_SUCCESS ; 
 int /*<<< orphan*/  RPC_INIT () ; 
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  client_tls ; 
 int /*<<< orphan*/  client_tls_mutex ; 
 int /*<<< orphan*/  client_tls_process ; 
 scalar_t__ platform_mutex_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_tls_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_tls_destroy (int /*<<< orphan*/ ) ; 

bool client_process_attach()
{
   KHR_STATUS_T status;
   status = platform_tls_create(&client_tls);
   if (status != KHR_SUCCESS) {
      return false;
   }

#ifdef CLIENT_THREAD_IS_PROCESS
   status = platform_tls_create(&client_tls_process);
   if (status != KHR_SUCCESS) {
      return false;
   }

   status = platform_tls_create(&client_tls_mutex);
   if (status != KHR_SUCCESS) {
      return false;
   }
#endif

   status = platform_mutex_create(&client_mutex);

   if (status != KHR_SUCCESS) {
      platform_tls_destroy(client_tls);
      return false;
   }
   if (!RPC_INIT()) {
      platform_mutex_destroy(&client_mutex);
      platform_tls_destroy(client_tls);
      return false;
   }
   return true;
}