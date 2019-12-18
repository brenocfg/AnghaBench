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

/* Variables and functions */
 int /*<<< orphan*/  RPC_TERM () ; 
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  client_tls ; 
 int /*<<< orphan*/  client_tls_process ; 
 int /*<<< orphan*/  platform_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_tls_destroy (int /*<<< orphan*/ ) ; 

void client_process_detach()
{
   RPC_TERM();
   platform_tls_destroy(client_tls);
   platform_mutex_destroy(&client_mutex);

#ifdef CLIENT_THREAD_IS_PROCESS
	platform_tls_destroy(client_tls_process);
#endif
}