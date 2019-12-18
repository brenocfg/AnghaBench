#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pack; int /*<<< orphan*/  unpack; } ;
struct TYPE_5__ {TYPE_1__ alignment; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int GLenum ;
typedef  TYPE_2__ GLXX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 TYPE_2__* GLXX_GET_CLIENT_STATE (int /*<<< orphan*/ *) ; 
#define  GL_PACK_ALIGNMENT 129 
#define  GL_UNPACK_ALIGNMENT 128 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_integer_internal_20(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLint *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   vcos_assert(state != NULL);

   switch (pname) {
   case GL_UNPACK_ALIGNMENT:
      params[0] = state->alignment.unpack;
      return 1;
   case GL_PACK_ALIGNMENT:
      params[0] = state->alignment.pack;
      return 1;
   default:
      UNREACHABLE();
      break;
   }

   return 0;
}