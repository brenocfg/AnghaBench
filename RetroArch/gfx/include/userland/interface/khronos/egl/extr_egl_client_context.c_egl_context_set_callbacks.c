#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void (* render_callback ) () ;void (* flush_callback ) (int) ;} ;
typedef  TYPE_1__ VG_CLIENT_STATE_T ;
struct TYPE_7__ {int type; scalar_t__ state; } ;
struct TYPE_6__ {void (* render_callback ) () ;void (* flush_callback ) (int) ;} ;
typedef  TYPE_2__ GLXX_CLIENT_STATE_T ;
typedef  TYPE_3__ EGL_CONTEXT_T ;

/* Variables and functions */
#define  OPENGL_ES_11 130 
#define  OPENGL_ES_20 129 
#define  OPENVG 128 
 int /*<<< orphan*/  UNREACHABLE () ; 

void egl_context_set_callbacks(EGL_CONTEXT_T *context,
                               void (*gl_render_callback)(void),
                               void (*gl_flush_callback)(bool),
                               void (*vg_render_callback)(void),
                               void (*vg_flush_callback)(bool))
{
   switch (context->type) {
      case OPENGL_ES_11:
      {
         GLXX_CLIENT_STATE_T *state = (GLXX_CLIENT_STATE_T *)context->state;
         state->render_callback = gl_render_callback;
         state->flush_callback = gl_flush_callback;
         break;
      }
      case OPENGL_ES_20:
      {
         GLXX_CLIENT_STATE_T *state = (GLXX_CLIENT_STATE_T *)context->state;
         state->render_callback = gl_render_callback;
         state->flush_callback = gl_flush_callback;
         break;
      }
      case OPENVG:
      {
         VG_CLIENT_STATE_T *state = (VG_CLIENT_STATE_T *)context->state;
         state->render_callback = vg_render_callback;
         state->flush_callback = vg_flush_callback;
         break;
      }
      default:
         UNREACHABLE();
   }
}