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
typedef  void* EGLImageKHR ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  EGLINTOPENMAXILDONEMARKER_ID ; 
 int /*<<< orphan*/  RPC_CALL2_RES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_EGLID (void*) ; 
 int RPC_INT_RES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglIntOpenMAXILDoneMarker_impl ; 

int eglIntOpenMAXILDoneMarker (void* component_handle, EGLImageKHR egl_image)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   int res;

   res = RPC_INT_RES(RPC_CALL2_RES(eglIntOpenMAXILDoneMarker_impl,
        thread, EGLINTOPENMAXILDONEMARKER_ID, RPC_EGLID(component_handle), RPC_EGLID(egl_image)));

   return res;
}