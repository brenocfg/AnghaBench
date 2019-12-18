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
struct TYPE_3__ {int /*<<< orphan*/  buffers; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ GLXX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GLXX_BUFFER_INFO_T ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_platform_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khrn_pointer_map_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * khrn_pointer_map_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buffer_info_delete(GLXX_CLIENT_STATE_T *state, GLuint buffer)
{
   GLXX_BUFFER_INFO_T *stored = khrn_pointer_map_lookup(&state->buffers, buffer);
   if(stored)
   {
      khrn_platform_free(stored);
      khrn_pointer_map_delete(&state->buffers,buffer);
   }
}