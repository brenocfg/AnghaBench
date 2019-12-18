#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct font_params {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  renderer_data; TYPE_1__* renderer; } ;
typedef  TYPE_2__ font_data_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* render_msg ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct font_params const*) ;} ;

/* Variables and functions */
 char* font_driver_reshape_msg (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct font_params const*) ; 
 void* video_font_driver ; 

void font_driver_render_msg(
      video_frame_info_t *video_info,
      void *font_data,
      const char *msg,
      const struct font_params *params)
{
   font_data_t *font = (font_data_t*)(font_data
         ? font_data : video_font_driver);

   if (msg && *msg && font && font->renderer && font->renderer->render_msg)
   {
#ifdef HAVE_LANGEXTRA
      char *new_msg = font_driver_reshape_msg(msg);
#else
      char *new_msg = (char*)msg;
#endif

      font->renderer->render_msg(video_info,
            font->renderer_data, new_msg, params);
#ifdef HAVE_LANGEXTRA
      free(new_msg);
#endif
   }
}