#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ queue; scalar_t__ audio_opened; } ;
struct TYPE_7__ {int /*<<< orphan*/  input; scalar_t__ input_num; TYPE_1__* priv; } ;
struct TYPE_6__ {TYPE_3__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  SDL_CloseAudio () ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_ports_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vcos_free (TYPE_3__*) ; 

__attribute__((used)) static MMAL_STATUS_T sdl_component_destroy(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;

   if (module->audio_opened)
      SDL_CloseAudio();
   SDL_QuitSubSystem(SDL_INIT_AUDIO);

   if(component->input_num) mmal_ports_free(component->input, 1);
   if(module->queue) mmal_queue_destroy(module->queue);
   vcos_free(module);
   return MMAL_SUCCESS;
}