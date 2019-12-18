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
typedef  int /*<<< orphan*/  VG_CLIENT_STATE_T ;
struct TYPE_3__ {int is_destroyed; int type; scalar_t__ state; int /*<<< orphan*/  servercontext; int /*<<< orphan*/  is_current; } ;
typedef  int /*<<< orphan*/  GLXX_CLIENT_STATE_T ;
typedef  TYPE_1__ EGL_CONTEXT_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  EGLINTDESTROYGL_ID ; 
 int /*<<< orphan*/  EGLINTDESTROYVG_ID ; 
#define  OPENGL_ES_11 130 
#define  OPENGL_ES_20 129 
#define  OPENVG 128 
 int /*<<< orphan*/  RPC_CALL1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_FLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_UINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int /*<<< orphan*/  eglIntDestroyGL_impl ; 
 int /*<<< orphan*/  eglIntDestroyVG_impl ; 
 int /*<<< orphan*/  glxx_client_state_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vg_client_state_free (int /*<<< orphan*/ *) ; 

void egl_context_term(EGL_CONTEXT_T *context)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   /* If we're current then there should still be a reference to us */
   /* (if this wasn't the case we should call egl_context_release_surfaces here) */
   vcos_assert(!context->is_current);
   vcos_assert(context->is_destroyed);

   switch (context->type) {
#ifndef NO_OPENVG
   case OPENVG:
      RPC_CALL1(eglIntDestroyVG_impl,
                thread,
                EGLINTDESTROYVG_ID,
                RPC_UINT(context->servercontext));
      RPC_FLUSH(thread);
      vg_client_state_free((VG_CLIENT_STATE_T *)context->state);
      break;
#endif
   case OPENGL_ES_11:
   case OPENGL_ES_20:
       RPC_CALL1(eglIntDestroyGL_impl,
                thread,
                EGLINTDESTROYGL_ID,
                RPC_UINT(context->servercontext));
      RPC_FLUSH(thread);
      glxx_client_state_free((GLXX_CLIENT_STATE_T *)context->state);
      break;
   default:
      UNREACHABLE();
   }

   context->state = 0;
}