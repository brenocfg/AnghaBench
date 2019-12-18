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
struct TYPE_3__ {int type; int status; int condition; } ;
typedef  int EGLint ;
typedef  TYPE_1__ EGL_SYNC_T ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_FALSE ; 
#define  EGL_SYNC_CONDITION_KHR 130 
#define  EGL_SYNC_STATUS_KHR 129 
#define  EGL_SYNC_TYPE_KHR 128 
 int /*<<< orphan*/  EGL_TRUE ; 

__attribute__((used)) static EGLBoolean egl_sync_get_attrib(EGL_SYNC_T *sync, EGLint attrib, EGLint *value)
{
   switch (attrib) {
   case EGL_SYNC_TYPE_KHR:
      *value = sync->type;
      return EGL_TRUE;
   case EGL_SYNC_STATUS_KHR:
      *value = sync->status;
      return EGL_TRUE;
   case EGL_SYNC_CONDITION_KHR:
      *value = sync->condition;
      return EGL_TRUE;
   default:
      return EGL_FALSE;
   }
}