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
typedef  int /*<<< orphan*/  VIDTEX_T ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  SVP_STOP_ERROR ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vidtex_stop_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vidtex_check_gl(VIDTEX_T *vt, uint32_t line)
{
   GLenum error = glGetError();
   int abort = 0;
   while (error != GL_NO_ERROR)
   {
      vcos_log_error("GL error: line %d error 0x%04x", line, error);
      abort = 1;
      error = glGetError();
   }
   if (abort)
      vidtex_stop_cb(vt, SVP_STOP_ERROR);
}