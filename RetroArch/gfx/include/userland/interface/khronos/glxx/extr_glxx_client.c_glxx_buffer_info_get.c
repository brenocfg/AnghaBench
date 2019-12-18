#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffers; } ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ GLXX_CLIENT_STATE_T ;
typedef  TYPE_2__ GLXX_BUFFER_INFO_T ;

/* Variables and functions */
 scalar_t__ get_bound_buffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* khrn_pointer_map_lookup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void glxx_buffer_info_get(GLXX_CLIENT_STATE_T *state, GLenum target, GLXX_BUFFER_INFO_T* buffer_info)
{
   GLuint buffer = get_bound_buffer(state, target);

   memset(buffer_info,0,sizeof(GLXX_BUFFER_INFO_T));

   buffer_info->id = 0;

   if(buffer != 0)
   {
      GLXX_BUFFER_INFO_T *stored = khrn_pointer_map_lookup(&state->buffers, buffer);
      if(stored)
         *buffer_info = *stored;
   }
}