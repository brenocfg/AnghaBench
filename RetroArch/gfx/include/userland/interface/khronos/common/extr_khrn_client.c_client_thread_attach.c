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
typedef  int /*<<< orphan*/  PLATFORM_MUTEX_T ;
typedef  scalar_t__ KHR_STATUS_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 scalar_t__ KHR_SUCCESS ; 
 int /*<<< orphan*/  client_send_make_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_thread_state_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_tls ; 
 int /*<<< orphan*/  client_tls_mutex ; 
 int /*<<< orphan*/  khrn_platform_free (int /*<<< orphan*/ *) ; 
 scalar_t__ khrn_platform_malloc (int,char*) ; 
 scalar_t__ platform_mutex_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_tls_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_tls_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_tls_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool client_thread_attach()
{
   CLIENT_THREAD_STATE_T *state = (CLIENT_THREAD_STATE_T *)khrn_platform_malloc(sizeof(CLIENT_THREAD_STATE_T), "CLIENT_THREAD_STATE_T");

   if (!state)
      return false;

   client_thread_state_init(state);

   platform_tls_set(client_tls, state);

#ifdef CLIENT_THREAD_IS_PROCESS
	{  //add mutex into thread's tls
		KHR_STATUS_T status;
		PLATFORM_MUTEX_T *local_mutex = (PLATFORM_MUTEX_T*)vcos_tls_get(client_tls_mutex);

		if (!local_mutex)
		{
			local_mutex = (PLATFORM_MUTEX_T*)khrn_platform_malloc(sizeof(PLATFORM_MUTEX_T),"thread mutex");
			if (!local_mutex)
				return false;

			status = platform_mutex_create(local_mutex);
			if (status != KHR_SUCCESS) {
				khrn_platform_free(local_mutex);
				return false;
			}

			vcos_tls_set(client_tls_mutex,local_mutex);
		}
	}
#endif

#ifndef RPC_LIBRARY    //TODO
   client_send_make_current(state);
#endif
   return true;
}