#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  sema; int /*<<< orphan*/  client; int /*<<< orphan*/  list; int /*<<< orphan*/  audio_render; int /*<<< orphan*/  user_buffer_list; } ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_1__ AUDIOPLAY_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ILC_GET_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMX_CommandStateSet ; 
 scalar_t__ OMX_Deinit () ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMX_StateIdle ; 
 int /*<<< orphan*/  OMX_StateLoaded ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ilclient_change_component_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilclient_cleanup_components (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilclient_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilclient_disable_port_buffers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 

int32_t audioplay_delete(AUDIOPLAY_STATE_T *st)
{
   OMX_ERRORTYPE error;

   ilclient_change_component_state(st->audio_render, OMX_StateIdle);

   error = OMX_SendCommand(ILC_GET_HANDLE(st->audio_render), OMX_CommandStateSet, OMX_StateLoaded, NULL);
   assert(error == OMX_ErrorNone);

   ilclient_disable_port_buffers(st->audio_render, 100, st->user_buffer_list, NULL, NULL);
   ilclient_change_component_state(st->audio_render, OMX_StateLoaded);
   ilclient_cleanup_components(st->list);

   error = OMX_Deinit();
   assert(error == OMX_ErrorNone);

   ilclient_destroy(st->client);

   sem_destroy(&st->sema);
   free(st);

   return 0;
}