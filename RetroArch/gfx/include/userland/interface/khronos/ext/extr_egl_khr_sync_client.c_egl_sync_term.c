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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  master; int /*<<< orphan*/  serversync; } ;
typedef  TYPE_1__ EGL_SYNC_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  EGLINTDESTROYSYNC_ID ; 
 scalar_t__ EGL_SYNC_FENCE_KHR ; 
 int /*<<< orphan*/  RPC_CALL1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_UINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglIntDestroySync_impl ; 
 int /*<<< orphan*/  khronos_platform_semaphore_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void egl_sync_term(EGL_SYNC_T *sync_master)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
#if SYNC_FENCE_KHR_SHORTCUT == 1
   if (sync_master->type != EGL_SYNC_FENCE_KHR)
#endif
   {
      RPC_CALL1(eglIntDestroySync_impl,
                thread,
                EGLINTDESTROYSYNC_ID,
                RPC_UINT(sync_master->serversync));
   }
   khronos_platform_semaphore_destroy(&sync_master->master);
}