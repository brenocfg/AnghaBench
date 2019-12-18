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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int EGL_CONTEXT_TYPE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_SERVER_GL11 ; 
 int /*<<< orphan*/  EGL_SERVER_GL20 ; 
#define  OPENGL_ES_11 129 
#define  OPENGL_ES_20 128 
 int /*<<< orphan*/  UNREACHABLE () ; 

__attribute__((used)) static uint32_t convert_gltype(EGL_CONTEXT_TYPE_T type)
{
   switch (type) {
   case OPENGL_ES_11: return EGL_SERVER_GL11;
   case OPENGL_ES_20: return EGL_SERVER_GL20;
   default:           UNREACHABLE(); return 0;
   }
}