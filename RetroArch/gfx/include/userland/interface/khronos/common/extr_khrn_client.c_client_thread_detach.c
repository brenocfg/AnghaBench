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
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;
typedef  int /*<<< orphan*/  CLIENT_PROCESS_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_PROCESS_STATE () ; 
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  client_thread_state_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_tls ; 
 int /*<<< orphan*/  client_tls_mutex ; 
 int /*<<< orphan*/  client_tls_process ; 
 int /*<<< orphan*/  khrn_platform_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_maybe_free_process () ; 
 int /*<<< orphan*/  platform_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_tls_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_tls_get (int /*<<< orphan*/ ) ; 

void client_thread_detach(void *dummy)
{
   CLIENT_THREAD_STATE_T *state = CLIENT_GET_THREAD_STATE();
   UNUSED(dummy);

   platform_tls_remove(client_tls);
   client_thread_state_term(state);

   khrn_platform_free(state);
   platform_maybe_free_process();

#ifdef CLIENT_THREAD_IS_PROCESS
	{
		CLIENT_PROCESS_STATE_T *process = CLIENT_GET_PROCESS_STATE();
   	khrn_platform_free(process);
		platform_tls_remove(client_tls_process);
	}

	{
		PLATFORM_MUTEX_T *local_mutex = (PLATFORM_MUTEX_T*)vcos_tls_get(client_tls_mutex);
		vcos_assert(local_mutex);

		platform_mutex_destroy(local_mutex);

		khrn_platform_free(local_mutex);
		platform_tls_remove(client_tls_mutex);
	}
#endif
}