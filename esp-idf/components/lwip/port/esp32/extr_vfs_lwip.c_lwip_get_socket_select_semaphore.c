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
 scalar_t__ sys_thread_sem_get () ; 

__attribute__((used)) static void *lwip_get_socket_select_semaphore(void)
{
    /* Calling this from the same process as select() will ensure that the semaphore won't be allocated from
     * ISR (lwip_stop_socket_select_isr).
     */
    return (void *) sys_thread_sem_get();
}