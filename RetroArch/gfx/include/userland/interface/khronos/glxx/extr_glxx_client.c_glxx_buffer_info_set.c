#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ id; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffers; } ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ GLXX_CLIENT_STATE_T ;
typedef  TYPE_2__ GLXX_BUFFER_INFO_T ;

/* Variables and functions */
 scalar_t__ get_bound_buffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* khrn_platform_malloc (int,char*) ; 
 int /*<<< orphan*/  khrn_pointer_map_insert (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*) ; 
 TYPE_2__* khrn_pointer_map_lookup (int /*<<< orphan*/ *,scalar_t__) ; 

void glxx_buffer_info_set(GLXX_CLIENT_STATE_T *state, GLenum target, GLXX_BUFFER_INFO_T* buffer_info)
{
   GLuint buffer = get_bound_buffer(state, target);

   if(buffer != 0)
   {
      GLXX_BUFFER_INFO_T *stored = khrn_pointer_map_lookup(&state->buffers, buffer);
      if(!stored)
      {
         stored = khrn_platform_malloc(sizeof(GLXX_BUFFER_INFO_T), "GLXX_BUFFER_INFO_T");
         khrn_pointer_map_insert(&state->buffers, buffer, stored);
      }
      buffer_info->id = buffer;
      //copy into stored
      *stored = *buffer_info;
   }
}