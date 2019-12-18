#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct nbio_t {int dummy; } ;
struct TYPE_12__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_13__ {int status; int type; int /*<<< orphan*/  is_finished; struct nbio_t* handle; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ nbio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NBIO_READ ; 
#define  NBIO_STATUS_INIT 141 
#define  NBIO_STATUS_TRANSFER 140 
#define  NBIO_STATUS_TRANSFER_FINISHED 139 
#define  NBIO_STATUS_TRANSFER_PARSE 138 
#define  NBIO_TYPE_BMP 137 
#define  NBIO_TYPE_FLAC 136 
#define  NBIO_TYPE_JPEG 135 
#define  NBIO_TYPE_MOD 134 
#define  NBIO_TYPE_MP3 133 
#define  NBIO_TYPE_NONE 132 
#define  NBIO_TYPE_OGG 131 
#define  NBIO_TYPE_PNG 130 
#define  NBIO_TYPE_TGA 129 
#define  NBIO_TYPE_WAV 128 
 int /*<<< orphan*/  nbio_begin_read (struct nbio_t*) ; 
 scalar_t__ nbio_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_audio_mixer_load_handler (TYPE_1__*) ; 
 int task_file_transfer_iterate_parse (TYPE_2__*) ; 
 int task_file_transfer_iterate_transfer (TYPE_2__*) ; 
 scalar_t__ task_get_cancelled (TYPE_1__*) ; 
 int /*<<< orphan*/  task_image_load_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  task_set_cancelled (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_finished (TYPE_1__*,int) ; 

void task_file_load_handler(retro_task_t *task)
{
   nbio_handle_t         *nbio  = (nbio_handle_t*)task->state;

   if (nbio)
   {
      switch (nbio->status)
      {
         case NBIO_STATUS_INIT:
            if (nbio && !string_is_empty(nbio->path))
            {
               struct nbio_t *handle = (struct nbio_t*)nbio_open(nbio->path, NBIO_READ);

               if (handle)
               {
                  nbio->handle       = handle;
                  nbio->status       = NBIO_STATUS_TRANSFER;

                  nbio_begin_read(handle);
                  return;
               }
               else
                  task_set_cancelled(task, true);
            }
            break;
         case NBIO_STATUS_TRANSFER_PARSE:
            if (!nbio || task_file_transfer_iterate_parse(nbio) == -1)
               task_set_cancelled(task, true);
            nbio->status = NBIO_STATUS_TRANSFER_FINISHED;
            break;
         case NBIO_STATUS_TRANSFER:
            if (!nbio || task_file_transfer_iterate_transfer(nbio) == -1)
               nbio->status = NBIO_STATUS_TRANSFER_PARSE;
            break;
         case NBIO_STATUS_TRANSFER_FINISHED:
            break;
      }

      switch (nbio->type)
      {
         case NBIO_TYPE_PNG:
         case NBIO_TYPE_JPEG:
         case NBIO_TYPE_TGA:
         case NBIO_TYPE_BMP:
            if (!task_image_load_handler(task))
               task_set_finished(task, true);
            break;
         case NBIO_TYPE_MP3:
         case NBIO_TYPE_FLAC:
         case NBIO_TYPE_OGG:
         case NBIO_TYPE_MOD:
         case NBIO_TYPE_WAV:
#ifdef HAVE_AUDIOMIXER
            if (!task_audio_mixer_load_handler(task))
               task_set_finished(task, true);
#endif
            break;
         case NBIO_TYPE_NONE:
         default:
            if (nbio->is_finished)
               task_set_finished(task, true);
            break;
      }
   }

   if (task_get_cancelled(task))
   {
      task_set_error(task, strdup("Task canceled."));
      task_set_finished(task, true);
   }
}