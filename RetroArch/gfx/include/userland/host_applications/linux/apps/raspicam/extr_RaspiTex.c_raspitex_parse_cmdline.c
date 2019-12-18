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
struct TYPE_3__ {int gl_win_defined; int /*<<< orphan*/  scene_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
#define  CommandGLScene 129 
#define  CommandGLWin 128 
 int /*<<< orphan*/  DEFAULT_HEIGHT ; 
 int /*<<< orphan*/  DEFAULT_WIDTH ; 
 int /*<<< orphan*/  RASPITEX_SCENE_MIRROR ; 
 int /*<<< orphan*/  RASPITEX_SCENE_SOBEL ; 
 int /*<<< orphan*/  RASPITEX_SCENE_SQUARE ; 
 int /*<<< orphan*/  RASPITEX_SCENE_TEAPOT ; 
 int /*<<< orphan*/  RASPITEX_SCENE_VCSM_SQUARE ; 
 int /*<<< orphan*/  RASPITEX_SCENE_YUV ; 
 int /*<<< orphan*/  cmdline_commands ; 
 int /*<<< orphan*/  cmdline_commands_size ; 
 int raspicli_get_command_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int*) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,char const*) ; 

int raspitex_parse_cmdline(RASPITEX_STATE *state,
                           const char *arg1, const char *arg2)
{
   int command_id, used = 0, num_parameters;

   if (!arg1)
      return 0;

   command_id = raspicli_get_command_id(cmdline_commands,
                                        cmdline_commands_size, arg1, &num_parameters);

   // If invalid command, or we are missing a parameter, drop out
   if (command_id==-1 || (command_id != -1 && num_parameters > 0 && arg2 == NULL))
      return 0;

   switch (command_id)
   {
   case CommandGLWin: // Allows a GL window to be different to preview-res
   {
      int tmp;
      tmp = sscanf(arg2, "%d,%d,%d,%d",
                   &state->x, &state->y, &state->width, &state->height);
      if (tmp != 4)
      {
         // Default to safe size on parse error
         state->x = state->y = 0;
         state->width = DEFAULT_WIDTH;
         state->height = DEFAULT_HEIGHT;
      }
      else
      {
         state->gl_win_defined = 1;
      }

      used = 2;
      break;
   }

   case CommandGLScene: // Selects the GL scene
   {
      if (strcmp(arg2, "square") == 0)
         state->scene_id = RASPITEX_SCENE_SQUARE;
      else if (strcmp(arg2, "teapot") == 0)
         state->scene_id = RASPITEX_SCENE_TEAPOT;
      else if (strcmp(arg2, "mirror") == 0)
         state->scene_id = RASPITEX_SCENE_MIRROR;
      else if (strcmp(arg2, "yuv") == 0)
         state->scene_id = RASPITEX_SCENE_YUV;
      else if (strcmp(arg2, "sobel") == 0)
         state->scene_id = RASPITEX_SCENE_SOBEL;
      else if (strcmp(arg2, "vcsm_square") == 0)
         state->scene_id = RASPITEX_SCENE_VCSM_SQUARE;
      else
         vcos_log_error("Unknown scene %s", arg2);

      used = 2;
      break;
   }
   }
   return used;
}