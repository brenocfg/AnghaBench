#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_10__ {TYPE_3__* gl; int /*<<< orphan*/  font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_4__ gl1_raster_t ;
struct TYPE_8__ {float height; } ;
struct TYPE_9__ {TYPE_2__ vp; } ;
struct TYPE_7__ {scalar_t__ (* get_line_height ) (int /*<<< orphan*/ ) ;} ;
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  gl1_raster_font_render_line (TYPE_4__*,char const*,unsigned int,float,float const*,float,float,unsigned int,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl1_raster_font_render_message(
      gl1_raster_t *font, const char *msg, GLfloat scale,
      const GLfloat color[4], GLfloat pos_x, GLfloat pos_y,
      unsigned text_align,
      video_frame_info_t *video_info)
{
   float line_height;
   int lines = 0;

   /* If the font height is not supported just draw as usual */
   if (!font->font_driver->get_line_height)
   {
      gl1_raster_font_render_line(font,
            msg, (unsigned)strlen(msg), scale, color, pos_x,
            pos_y, text_align,
            video_info);
      return;
   }

   line_height = (float) font->font_driver->get_line_height(font->font_data) *
                     scale / font->gl->vp.height;

   for (;;)
   {
      const char *delim = strchr(msg, '\n');
      unsigned msg_len  = delim
         ? (unsigned)(delim - msg) : (unsigned)strlen(msg);

      /* Draw the line */
      gl1_raster_font_render_line(font,
            msg, msg_len, scale, color, pos_x,
            pos_y - (float)lines*line_height, text_align,
            video_info);

      if (!delim)
         break;

      msg += msg_len + 1;
      lines++;
   }
}