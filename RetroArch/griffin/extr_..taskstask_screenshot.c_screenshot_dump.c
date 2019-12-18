#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {char* shotname; char* filename; int is_idle; int is_paused; int bgr24; unsigned int height; unsigned int width; int pitch; int widgets_ready; int silence; unsigned int pixel_format_type; struct TYPE_13__* out_buffer; scalar_t__ title; int /*<<< orphan*/  callback; int /*<<< orphan*/  handler; struct TYPE_13__* state; int /*<<< orphan*/  type; int /*<<< orphan*/  history_list_enable; void* userbuf; void const* frame; } ;
typedef  TYPE_2__ uint8_t ;
struct retro_system_info {char const* library_name; } ;
struct TYPE_12__ {scalar_t__ screenshots_in_content_dir; scalar_t__ auto_screenshot_filename; int /*<<< orphan*/  history_list_enable; } ;
struct TYPE_14__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
typedef  TYPE_2__ screenshot_task_state_t ;
typedef  int /*<<< orphan*/  screenshot_path ;
typedef  TYPE_2__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_EXT ; 
 int /*<<< orphan*/  MSG_TAKING_SCREENSHOT ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  TASK_TYPE_BLOCKING ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  core_get_system_info (struct retro_system_info*) ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char const*,int) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char*,int) ; 
 int /*<<< orphan*/  fill_str_dated_filename (char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (unsigned int) ; 
 int menu_widgets_ready () ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char const* path_basename (char const*) ; 
 scalar_t__ path_is_empty (int /*<<< orphan*/ ) ; 
 int screenshot_dump_direct (TYPE_2__*) ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  task_free_title (TYPE_2__*) ; 
 TYPE_2__* task_init () ; 
 scalar_t__ task_queue_push (TYPE_2__*) ; 
 int /*<<< orphan*/  task_screenshot_callback ; 
 int /*<<< orphan*/  task_screenshot_handler ; 

__attribute__((used)) static bool screenshot_dump(
      const char *screenshot_dir,
      const char *name_base,
      const void *frame,
      unsigned width,
      unsigned height,
      int pitch,
      bool bgr24,
      void *userbuf,
      bool savestate,
      bool is_idle,
      bool is_paused,
      bool fullpath,
      bool use_thread,
      unsigned pixel_format_type)
{
   struct retro_system_info system_info;
   uint8_t *buf                   = NULL;
   settings_t *settings           = config_get_ptr();
   screenshot_task_state_t *state = (screenshot_task_state_t*)calloc(1, sizeof(*state));

   state->shotname[0]             = '\0';

   /* If fullpath is true, name_base already contains a 
    * static path + filename to save the screenshot to. */
   if (fullpath)
      strlcpy(state->filename, name_base, sizeof(state->filename));

   state->is_idle             = is_idle;
   state->is_paused           = is_paused;
   state->bgr24               = bgr24;
   state->height              = height;
   state->width               = width;
   state->pitch               = pitch;
   state->frame               = frame;
   state->userbuf             = userbuf;
#ifdef HAVE_MENU_WIDGETS
   state->widgets_ready       = menu_widgets_ready();
#else
   state->widgets_ready       = false;
#endif
   state->silence             = savestate;
   state->history_list_enable = settings->bools.history_list_enable;
   state->pixel_format_type   = pixel_format_type;

   if (!fullpath)
   {
      if (savestate)
      {
         strlcpy(state->filename,
               name_base, sizeof(state->filename));
         strlcat(state->filename, ".png", sizeof(state->filename));
      }
      else
      {
         if (settings->bools.auto_screenshot_filename)
         {
            const char *screenshot_name = NULL;

            if (path_is_empty(RARCH_PATH_CONTENT))
            {
               if (!core_get_system_info(&system_info))
                  return false;

               if (string_is_empty(system_info.library_name))
                  screenshot_name = "RetroArch";
               else
                  screenshot_name = system_info.library_name;
            }
            else
               screenshot_name = path_basename(name_base);

            fill_str_dated_filename(state->shotname, screenshot_name,
                  IMG_EXT, sizeof(state->shotname));
         }
         else
         {
            strlcpy(state->shotname, path_basename(name_base),
                  sizeof(state->shotname));
            strlcat(state->shotname, ".png", sizeof(state->shotname));
         }

         if (  string_is_empty(screenshot_dir) || 
               settings->bools.screenshots_in_content_dir)
         {
            char screenshot_path[PATH_MAX_LENGTH];
            screenshot_path[0]             = '\0';
            fill_pathname_basedir(screenshot_path, name_base,
                  sizeof(screenshot_path));
            fill_pathname_join(state->filename, screenshot_path,
                  state->shotname, sizeof(state->filename));
         }
         else
            fill_pathname_join(state->filename, screenshot_dir,
                  state->shotname, sizeof(state->filename));
      }
   }

#if defined(HAVE_RPNG)
   buf = (uint8_t*)malloc(width * height * 3);
   if (!buf)
   {
      free(state);
      return false;
   }
   state->out_buffer = buf;
#endif

   if (use_thread)
   {
      retro_task_t *task = task_init();

      task->type        = TASK_TYPE_BLOCKING;
      task->state       = state;
      task->handler     = task_screenshot_handler;
#ifdef HAVE_MENU_WIDGETS
      task->callback    = task_screenshot_callback;
#endif
#if defined(HAVE_MENU) && defined(HAVE_MENU_WIDGETS)
      if (state->widgets_ready && !savestate)
         task_free_title(task);
      else
#endif
      {
         if (!savestate)
            task->title = strdup(msg_hash_to_str(MSG_TAKING_SCREENSHOT));
      }

      if (task_queue_push(task))
         return true;

      /* There is already a blocking task going on */
      if (task->title)
         task_free_title(task);

      free(task);

      if (state->out_buffer)
         free(state->out_buffer);

      free(state);

      return false;
   }

   return screenshot_dump_direct(state);
}