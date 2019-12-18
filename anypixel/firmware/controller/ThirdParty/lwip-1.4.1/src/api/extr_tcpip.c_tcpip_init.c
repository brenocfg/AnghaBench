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
typedef  int /*<<< orphan*/  tcpip_init_done_fn ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPIP_MBOX_SIZE ; 
 int /*<<< orphan*/  TCPIP_THREAD_NAME ; 
 int /*<<< orphan*/  TCPIP_THREAD_PRIO ; 
 int /*<<< orphan*/  TCPIP_THREAD_STACKSIZE ; 
 int /*<<< orphan*/  lock_tcpip_core ; 
 int /*<<< orphan*/  lwip_init () ; 
 int /*<<< orphan*/  mbox ; 
 scalar_t__ sys_mbox_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sys_mutex_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_thread_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpip_init_done ; 
 void* tcpip_init_done_arg ; 
 int /*<<< orphan*/  tcpip_thread ; 

void
tcpip_init(tcpip_init_done_fn initfunc, void *arg)
{
  lwip_init();

  tcpip_init_done = initfunc;
  tcpip_init_done_arg = arg;
  if(sys_mbox_new(&mbox, TCPIP_MBOX_SIZE) != ERR_OK) {
    LWIP_ASSERT("failed to create tcpip_thread mbox", 0);
  }
#if LWIP_TCPIP_CORE_LOCKING
  if(sys_mutex_new(&lock_tcpip_core) != ERR_OK) {
    LWIP_ASSERT("failed to create lock_tcpip_core", 0);
  }
#endif /* LWIP_TCPIP_CORE_LOCKING */

  sys_thread_new(TCPIP_THREAD_NAME, tcpip_thread, NULL, TCPIP_THREAD_STACKSIZE, TCPIP_THREAD_PRIO);
}