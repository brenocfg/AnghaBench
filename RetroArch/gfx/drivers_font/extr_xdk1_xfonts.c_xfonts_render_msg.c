#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  surf; TYPE_5__* debug_font; TYPE_1__* d3d; } ;
typedef  TYPE_2__ xfonts_t ;
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_8__ {float font_msg_pos_x; float font_msg_pos_y; } ;
typedef  TYPE_3__ video_frame_info_t ;
struct font_params {float x; float y; } ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_9__ {int /*<<< orphan*/  (* TextOut ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,float,float) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3DBACKBUFFER_TYPE_MONO ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  XFONT_TextOut (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,float,float) ; 
 int /*<<< orphan*/  d3d8_device_get_backbuffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_surface_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,float,float) ; 

__attribute__((used)) static void xfonts_render_msg(
      video_frame_info_t *video_info,
      void *data, const char *msg,
      const struct font_params *params)
{
   wchar_t str[PATH_MAX_LENGTH];
   float x, y;
   xfonts_t *xfonts                 = (xfonts_t*)data;

   if (params)
   {
      x = params->x;
      y = params->y;
   }
   else
   {
      x = video_info->font_msg_pos_x;
      y = video_info->font_msg_pos_y;
   }

   d3d8_device_get_backbuffer(xfonts->d3d->dev,
         -1, 0, D3DBACKBUFFER_TYPE_MONO, &xfonts->surf);

   mbstowcs(str, msg, sizeof(str) / sizeof(wchar_t));

#ifdef __cplusplus
   xfonts->debug_font->TextOut(xfonts->surf, str, (unsigned)-1, x, y);
#else
   XFONT_TextOut(xfonts->debug_font, xfonts->surf, str, (unsigned)-1, x, y);
#endif
   d3d8_surface_free(xfonts->surf);
}