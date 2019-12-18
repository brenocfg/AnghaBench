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
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  GLXX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/ * GLXX_GET_CLIENT_STATE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_OPENGLES_API (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxx_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void glxx_set_error_api(uint32_t api, GLenum error)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_API(thread, api))
   {
      GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);
      glxx_set_error(state, error);
   }
}