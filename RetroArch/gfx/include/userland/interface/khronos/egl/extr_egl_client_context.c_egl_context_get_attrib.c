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
struct TYPE_3__ {int renderbuffer; int /*<<< orphan*/  type; int /*<<< orphan*/  configname; } ;
typedef  int EGLint ;
typedef  TYPE_1__ EGL_CONTEXT_T ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
#define  EGL_CONFIG_ID 134 
#define  EGL_CONTEXT_CLIENT_TYPE 133 
#define  EGL_CONTEXT_CLIENT_VERSION 132 
 int /*<<< orphan*/  EGL_FALSE ; 
 int EGL_OPENGL_ES_API ; 
 int EGL_OPENVG_API ; 
#define  EGL_RENDER_BUFFER 131 
 int /*<<< orphan*/  EGL_TRUE ; 
#define  OPENGL_ES_11 130 
#define  OPENGL_ES_20 129 
#define  OPENVG 128 
 int /*<<< orphan*/  UNREACHABLE () ; 

EGLBoolean egl_context_get_attrib(EGL_CONTEXT_T *context, EGLint attrib, EGLint *value)
{
   switch (attrib) {
   case EGL_CONFIG_ID:
      *value = (int)(intptr_t)context->configname;
      return EGL_TRUE;
   case EGL_CONTEXT_CLIENT_TYPE:
      switch (context->type) {
      case OPENGL_ES_11:
      case OPENGL_ES_20:
         *value = EGL_OPENGL_ES_API;
         break;
      case OPENVG:
         *value = EGL_OPENVG_API;
         break;
      default:
         UNREACHABLE();
         break;
      }
      return EGL_TRUE;
   case EGL_CONTEXT_CLIENT_VERSION:
      switch (context->type) {
      case OPENGL_ES_11:
      case OPENVG:
         *value = 1;
         break;
      case OPENGL_ES_20:
         *value = 2;
         break;
      default:
         UNREACHABLE();
         break;
      }
      return EGL_TRUE;
   case EGL_RENDER_BUFFER:
   {
      /* TODO: GLES supposedly doesn't support single-buffered rendering. Should we take this into account? */
      *value = context->renderbuffer;
      return EGL_TRUE;
   }
   default:
      return EGL_FALSE;
   }
}