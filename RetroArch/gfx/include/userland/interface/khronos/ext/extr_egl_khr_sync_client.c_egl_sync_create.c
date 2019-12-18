#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int* name; int /*<<< orphan*/  master; int /*<<< orphan*/  serversync; scalar_t__ status; scalar_t__ type; scalar_t__ threshold; scalar_t__ condition; } ;
typedef  scalar_t__ EGLint ;
typedef  scalar_t__ EGLenum ;
typedef  TYPE_1__ EGL_SYNC_T ;
typedef  scalar_t__ EGLSyncKHR ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  EGLINTCREATESYNCFENCE_ID ; 
 int /*<<< orphan*/  EGLINTCREATESYNC_ID ; 
 scalar_t__ EGL_SYNC_FENCE_KHR ; 
 scalar_t__ KHR_SUCCESS ; 
 int /*<<< orphan*/  RPC_CALL3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_CALL4_RES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_INT (scalar_t__) ; 
 int /*<<< orphan*/  RPC_UINT (scalar_t__) ; 
 int /*<<< orphan*/  RPC_UINT_RES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglIntCreateSyncFence_impl ; 
 int /*<<< orphan*/  eglIntCreateSync_impl ; 
 int /*<<< orphan*/  khrn_platform_free (TYPE_1__*) ; 
 scalar_t__ khrn_platform_malloc (int,char*) ; 
 scalar_t__ khronos_platform_semaphore_create (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  khronos_platform_semaphore_destroy (int /*<<< orphan*/ *) ; 
 int rpc_get_client_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static EGL_SYNC_T *egl_sync_create(EGLSyncKHR sync, EGLenum type,
      EGLint condition, EGLint threshold, EGLint status)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   EGL_SYNC_T *sync_ptr = (EGL_SYNC_T *)khrn_platform_malloc(sizeof(EGL_SYNC_T), "EGL_SYNC_T");
   uint64_t pid = rpc_get_client_id(thread);
   uint32_t sem;

   if (!sync_ptr)
      return 0;

   sync_ptr->condition = condition;
   sync_ptr->threshold = threshold;
   sync_ptr->type = type;
   sync_ptr->status = status;

   sync_ptr->name[0] = (int)pid;
   sync_ptr->name[1] = (int)(pid >> 32);
   sync_ptr->name[2] = (int)sync;

   if (khronos_platform_semaphore_create(&sync_ptr->master, sync_ptr->name, 0) != KHR_SUCCESS) {
      khrn_platform_free(sync_ptr);
      return 0;
   }

   sem = (uint32_t) sync;
#if SYNC_FENCE_KHR_SHORTCUT == 1
   if (type == EGL_SYNC_FENCE_KHR){
      RPC_CALL3(eglIntCreateSyncFence_impl,
                               thread,
                               EGLINTCREATESYNCFENCE_ID,
                               RPC_UINT(condition),
                               RPC_INT(threshold),
                               RPC_UINT(sem));
   } else
#endif
   {
      sync_ptr->serversync = RPC_UINT_RES(RPC_CALL4_RES(eglIntCreateSync_impl,
                                                 thread,
                                                 EGLINTCREATESYNC_ID,
                                                 RPC_UINT(type),
                                                 RPC_UINT(condition),
                                                 RPC_INT(threshold),
                                                 RPC_UINT(sem)));
      if (!sync_ptr->serversync) {
         khronos_platform_semaphore_destroy(&sync_ptr->master);
         khrn_platform_free(sync_ptr);
         return 0;
      }
   }
   return sync_ptr;
}