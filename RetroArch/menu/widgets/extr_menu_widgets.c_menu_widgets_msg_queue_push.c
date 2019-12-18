#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int video_font_size; } ;
struct TYPE_12__ {TYPE_1__ floats; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_13__ {char* title; int /*<<< orphan*/  progress; int /*<<< orphan*/  finished; int /*<<< orphan*/  cancelled; int /*<<< orphan*/  error; int /*<<< orphan*/  alternative_look; TYPE_4__* frontend_userdata; int /*<<< orphan*/  ident; } ;
typedef  TYPE_3__ retro_task_t ;
typedef  int /*<<< orphan*/  msg_widget ;
struct TYPE_14__ {unsigned int duration; float alpha; int dying; int expired; int expiration_timer_started; float msg_transition_animation; int text_height; int unfolded; int unfolding; float unfold; char* msg; unsigned int msg_len; char* task_title_ptr; int task_count; int width; int /*<<< orphan*/  task_progress; int /*<<< orphan*/  task_finished; int /*<<< orphan*/  task_cancelled; int /*<<< orphan*/  task_error; int /*<<< orphan*/ * msg_new; scalar_t__ expiration_timer; scalar_t__ hourglass_rotation; int /*<<< orphan*/  task_ident; TYPE_3__* task_ptr; scalar_t__ offset_y; } ;
typedef  TYPE_4__ menu_widget_msg_t ;
struct TYPE_15__ {uintptr_t tag; int duration; float target_value; float* subject; TYPE_4__* userdata; int /*<<< orphan*/  (* cb ) (TYPE_4__*) ;int /*<<< orphan*/  easing_enum; } ;
typedef  TYPE_5__ menu_animation_ctx_entry_t ;
typedef  enum message_queue_icon { ____Placeholder_message_queue_icon } message_queue_icon ;
typedef  enum message_queue_category { ____Placeholder_message_queue_category } message_queue_category ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int MSG_QUEUE_ANIMATION_DURATION ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,TYPE_4__**,int) ; 
 scalar_t__ fifo_write_avail (int /*<<< orphan*/ ) ; 
 int font_driver_get_message_width (int /*<<< orphan*/ ,char const*,unsigned int,int) ; 
 int /*<<< orphan*/  font_regular ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_5__*) ; 
 int /*<<< orphan*/  menu_timer_kill (scalar_t__*) ; 
 int /*<<< orphan*/  msg_queue ; 
 unsigned int msg_queue_default_rect_width ; 
 int msg_queue_glyph_width ; 
 scalar_t__ msg_queue_has_icons ; 
 float msg_queue_height ; 
 int msg_queue_text_scale_factor ; 
 int /*<<< orphan*/  msg_widget_msg_transition_animation_done (TYPE_4__*) ; 
 int simple_widget_padding ; 
 void* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  word_wrap (char*,char*,unsigned int,int,int) ; 

void menu_widgets_msg_queue_push(
      retro_task_t *task, const char *msg,
      unsigned duration,
      char *title,
      enum message_queue_icon icon,
      enum message_queue_category category,
      unsigned prio, bool flush)
{
   menu_widget_msg_t* msg_widget = NULL;

   if (fifo_write_avail(msg_queue) > 0)
   {
      /* Get current msg if it exists */
      if (task && task->frontend_userdata)
      {
         msg_widget           = (menu_widget_msg_t*) task->frontend_userdata;
         msg_widget->task_ptr = task; /* msg_widgets can be passed between tasks */
      }

      /* Spawn a new notification */
      if (!msg_widget)
      {
         const char *title                      = msg;

         msg_widget                             = (menu_widget_msg_t*)calloc(1, sizeof(*msg_widget));

         if (task)
            title                               = task->title;

         msg_widget->duration                   = duration;
         msg_widget->offset_y                   = 0;
         msg_widget->alpha                      = 1.0f;

         msg_widget->dying                      = false;
         msg_widget->expired                    = false;

         msg_widget->expiration_timer           = 0;
         msg_widget->task_ptr                   = task;
         msg_widget->expiration_timer_started   = false;

         msg_widget->msg_new                    = NULL;
         msg_widget->msg_transition_animation   = 0.0f;

         msg_widget->text_height                = 0;

         if (msg_queue_has_icons)
         {
            msg_widget->unfolded                = false;
            msg_widget->unfolding               = false;
            msg_widget->unfold                  = 0.0f;
         }
         else
         {
            msg_widget->unfolded                = true;
            msg_widget->unfolding               = false;
            msg_widget->unfold                  = 1.0f;
         }

         if (task)
         {
            msg_widget->msg                  = strdup(title);
            msg_widget->msg_len              = (unsigned)strlen(title);

            msg_widget->task_error           = task->error;
            msg_widget->task_cancelled       = task->cancelled;
            msg_widget->task_finished        = task->finished;
            msg_widget->task_progress        = task->progress;
            msg_widget->task_ident           = task->ident;
            msg_widget->task_title_ptr       = task->title;
            msg_widget->task_count           = 1;

            msg_widget->unfolded             = true;

            msg_widget->width                = font_driver_get_message_width(font_regular, title, msg_widget->msg_len, msg_queue_text_scale_factor) + simple_widget_padding/2;

            task->frontend_userdata          = msg_widget;

            msg_widget->hourglass_rotation   = 0;
         }
         else
         {
            /* Compute rect width, wrap if necessary */
            /* Single line text > two lines text > two lines text with expanded width */
            unsigned title_length   = (unsigned)strlen(title);
            char *msg               = strdup(title);
            unsigned width          = msg_queue_default_rect_width;
            unsigned text_width     = font_driver_get_message_width(font_regular, title, title_length, msg_queue_text_scale_factor);
            settings_t *settings    = config_get_ptr();

            msg_widget->text_height = msg_queue_text_scale_factor * settings->floats.video_font_size;

            /* Text is too wide, split it into two lines */
            if (text_width > width)
            {
               if (text_width/2 > width)
               {
                  width = text_width/2;
                  width += 10 * msg_queue_glyph_width;
               }

               word_wrap(msg, msg, title_length/2 + 10, false, 2);

               msg_widget->text_height *= 2.5f;
            }
            else
            {
               width                      = text_width;
               msg_widget->text_height    *= 1.35f;
            }

            msg_widget->msg         = msg;
            msg_widget->msg_len     = (unsigned)strlen(msg);
            msg_widget->width       = width + simple_widget_padding/2;
         }

         fifo_write(msg_queue, &msg_widget, sizeof(msg_widget));
      }
      /* Update task info */
      else
      {
         if (msg_widget->expiration_timer_started)
         {
            menu_timer_kill(&msg_widget->expiration_timer);
            msg_widget->expiration_timer_started = false;
         }

         if (task->title != msg_widget->task_title_ptr)
         {
            unsigned len         = (unsigned)strlen(task->title);
            unsigned new_width   = font_driver_get_message_width(font_regular, task->title, len, msg_queue_text_scale_factor);

            if (msg_widget->msg_new)
            {
               free(msg_widget->msg_new);
               msg_widget->msg_new = NULL;
            }

            msg_widget->msg_new                    = strdup(task->title);
            msg_widget->msg_len                    = len;
            msg_widget->task_title_ptr             = task->title;
            msg_widget->msg_transition_animation   = 0;

            if (!task->alternative_look)
            {
               menu_animation_ctx_entry_t entry;

               entry.easing_enum    = EASING_OUT_QUAD;
               entry.tag            = (uintptr_t) msg_widget;
               entry.duration       = MSG_QUEUE_ANIMATION_DURATION*2;
               entry.target_value   = msg_queue_height/2.0f;
               entry.subject        = &msg_widget->msg_transition_animation;
               entry.cb             = msg_widget_msg_transition_animation_done;
               entry.userdata       = msg_widget;

               menu_animation_push(&entry);
            }
            else
            {
               msg_widget_msg_transition_animation_done(msg_widget);
            }

            msg_widget->task_count++;

            msg_widget->width = new_width;
         }

         msg_widget->task_error        = task->error;
         msg_widget->task_cancelled    = task->cancelled;
         msg_widget->task_finished     = task->finished;
         msg_widget->task_progress     = task->progress;
      }
   }
}