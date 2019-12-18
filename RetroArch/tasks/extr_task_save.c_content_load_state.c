#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  state_slot; } ;
struct TYPE_10__ {TYPE_1__ ints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_11__ {int load_to_backup_buffer; int autoload; int /*<<< orphan*/  title; int /*<<< orphan*/  callback; int /*<<< orphan*/  handler; struct TYPE_11__* state; int /*<<< orphan*/  type; int /*<<< orphan*/  has_valid_framebuffer; int /*<<< orphan*/  state_slot; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ save_task_state_t ;
typedef  TYPE_3__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_LOADING_STATE ; 
 int /*<<< orphan*/  TASK_TYPE_BLOCKING ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  content_load_state_cb ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_3__* task_init () ; 
 int /*<<< orphan*/  task_load_handler ; 
 int /*<<< orphan*/  task_queue_push (TYPE_3__*) ; 
 int /*<<< orphan*/  video_driver_cached_frame_has_valid_framebuffer () ; 

bool content_load_state(const char *path,
      bool load_to_backup_buffer, bool autoload)
{
   retro_task_t       *task     = task_init();
   save_task_state_t *state     = (save_task_state_t*)calloc(1, sizeof(*state));
   settings_t *settings         = config_get_ptr();

   if (!task || !state)
      goto error;

   strlcpy(state->path, path, sizeof(state->path));
   state->load_to_backup_buffer = load_to_backup_buffer;
   state->autoload              = autoload;
   state->state_slot            = settings->ints.state_slot;
   state->has_valid_framebuffer = 
      video_driver_cached_frame_has_valid_framebuffer();

   task->type                   = TASK_TYPE_BLOCKING;
   task->state                  = state;
   task->handler                = task_load_handler;
   task->callback               = content_load_state_cb;
   task->title                  = strdup(msg_hash_to_str(MSG_LOADING_STATE));

   task_queue_push(task);

   return true;

error:
   if (state)
      free(state);
   if (task)
      free(task);

   return false;
}