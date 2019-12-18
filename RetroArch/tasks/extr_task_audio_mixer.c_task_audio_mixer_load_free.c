#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct audio_mixer_handle {int /*<<< orphan*/  (* cb ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_2__* buffer; } ;
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_8__ {int /*<<< orphan*/  handle; struct TYPE_8__* data; struct TYPE_8__* path; } ;
typedef  TYPE_2__ nbio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  nbio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void task_audio_mixer_load_free(retro_task_t *task)
{
   nbio_handle_t       *nbio        = (nbio_handle_t*)task->state;
   struct audio_mixer_handle *mixer = (struct audio_mixer_handle*)nbio->data;

   if (mixer)
   {
      if (mixer->buffer)
      {
         if (mixer->buffer->path)
            free(mixer->buffer->path);
         free(mixer->buffer);
      }

      if (mixer->cb)
         mixer->cb(task, NULL, NULL, NULL);
   }

   if (!string_is_empty(nbio->path))
      free(nbio->path);
   if (nbio->data)
      free(nbio->data);
   nbio_free(nbio->handle);
   free(nbio);
}