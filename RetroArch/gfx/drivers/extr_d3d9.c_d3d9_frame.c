#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;

/* Type definitions */
struct TYPE_24__ {unsigned int width; unsigned int height; char const* stat_text; scalar_t__ widgets_inited; int /*<<< orphan*/  osd_stat_params; scalar_t__ statistics_show; scalar_t__ black_frame_insertion; } ;
typedef  TYPE_3__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct font_params {int dummy; } ;
struct TYPE_23__ {scalar_t__ buffer; scalar_t__ decl; scalar_t__ offset; } ;
struct TYPE_25__ {int should_resize; unsigned int overlays_size; int /*<<< orphan*/  dev; TYPE_19__* overlays; int /*<<< orphan*/  mvp; scalar_t__ overlays_enabled; TYPE_2__ menu_display; TYPE_19__* menu; int /*<<< orphan*/  dev_rotation; TYPE_1__* renderchain_driver; scalar_t__ needs_restore; int /*<<< orphan*/  final_viewport; int /*<<< orphan*/  renderchain_data; } ;
typedef  TYPE_4__ d3d9_video_t ;
typedef  int /*<<< orphan*/  Vertex ;
struct TYPE_26__ {int MaxZ; unsigned int Width; unsigned int Height; scalar_t__ MinZ; scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* render ) (TYPE_4__*,TYPE_3__*,void const*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_final_viewport ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_21__ {scalar_t__ enabled; } ;
typedef  int /*<<< orphan*/  LPDIRECT3DVERTEXDECLARATION9 ;
typedef  int /*<<< orphan*/  LPDIRECT3DVERTEXBUFFER9 ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_5__ D3DVIEWPORT9 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCLEAR_TARGET ; 
 scalar_t__ IsIconic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  d3d9_begin_scene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_end_scene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_overlay_render (TYPE_4__*,TYPE_3__*,TYPE_19__*,int) ; 
 int /*<<< orphan*/  d3d9_restore (TYPE_4__*) ; 
 int /*<<< orphan*/  d3d9_set_mvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d9_set_stream_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d3d9_set_vertex_declaration (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_viewport (TYPE_4__*,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  d3d9_set_viewports (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  d3d9_swap (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_update_title (TYPE_3__*) ; 
 int /*<<< orphan*/  font_driver_render_msg (TYPE_3__*,int /*<<< orphan*/ *,char const*,struct font_params const*) ; 
 int /*<<< orphan*/  menu_driver_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_widgets_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_3__*,void const*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win32_get_window () ; 

__attribute__((used)) static bool d3d9_frame(void *data, const void *frame,
      unsigned frame_width, unsigned frame_height,
      uint64_t frame_count, unsigned pitch,
      const char *msg, video_frame_info_t *video_info)
{
   D3DVIEWPORT9 screen_vp;
   unsigned i                          = 0;
   d3d9_video_t *d3d                   = (d3d9_video_t*)data;
   unsigned width                      = video_info->width;
   unsigned height                     = video_info->height;
   (void)i;

   if (!frame)
      return true;

   /* We cannot recover in fullscreen. */
   if (d3d->needs_restore)
   {
#ifndef _XBOX
      HWND window = win32_get_window();
      if (IsIconic(window))
         return true;
#endif

      if (!d3d9_restore(d3d))
      {
         RARCH_ERR("[D3D9]: Failed to restore.\n");
         return false;
      }
   }

   if (d3d->should_resize)
   {
      d3d9_set_viewport(d3d, width, height, false, true);
      if (d3d->renderchain_driver->set_final_viewport)
         d3d->renderchain_driver->set_final_viewport(d3d,
               d3d->renderchain_data, &d3d->final_viewport);

      d3d->should_resize = false;
   }

   /* render_chain() only clears out viewport,
    * clear out everything. */
   screen_vp.X      = 0;
   screen_vp.Y      = 0;
   screen_vp.MinZ   = 0;
   screen_vp.MaxZ   = 1;
   screen_vp.Width  = width;
   screen_vp.Height = height;
   d3d9_set_viewports(d3d->dev, &screen_vp);
   d3d9_clear(d3d->dev, 0, 0, D3DCLEAR_TARGET, 0, 1, 0);

   /* Insert black frame first, so we
    * can screenshot, etc. */
   if (video_info->black_frame_insertion)
   {
      if (!d3d9_swap(d3d, d3d->dev) || d3d->needs_restore)
         return true;
      d3d9_clear(d3d->dev, 0, 0, D3DCLEAR_TARGET, 0, 1, 0);
   }

   if (!d3d->renderchain_driver->render(
            d3d, video_info,
            frame, frame_width, frame_height,
            pitch, d3d->dev_rotation))
   {
      RARCH_ERR("[D3D9]: Failed to render scene.\n");
      return false;
   }

#ifdef HAVE_MENU
   if (d3d->menu && d3d->menu->enabled)
   {
      d3d9_set_mvp(d3d->dev, &d3d->mvp);
      d3d9_overlay_render(d3d, video_info, d3d->menu, false);

      d3d->menu_display.offset = 0;
      d3d9_set_vertex_declaration(d3d->dev, (LPDIRECT3DVERTEXDECLARATION9)d3d->menu_display.decl);
      d3d9_set_stream_source(d3d->dev, 0, (LPDIRECT3DVERTEXBUFFER9)d3d->menu_display.buffer, 0, sizeof(Vertex));

      d3d9_set_viewports(d3d->dev, &screen_vp);
      menu_driver_frame(video_info);
   }
   else if (video_info->statistics_show)
   {
      struct font_params *osd_params = (struct font_params*)
         &video_info->osd_stat_params;

      if (osd_params)
      {
         d3d9_set_viewports(d3d->dev, &screen_vp);
         d3d9_begin_scene(d3d->dev);
         font_driver_render_msg(video_info, NULL, video_info->stat_text,
               (const struct font_params*)&video_info->osd_stat_params);
         d3d9_end_scene(d3d->dev);
      }
   }
#endif

#ifdef HAVE_OVERLAY
   if (d3d->overlays_enabled)
   {
      d3d9_set_mvp(d3d->dev, &d3d->mvp);
      for (i = 0; i < d3d->overlays_size; i++)
         d3d9_overlay_render(d3d, video_info, &d3d->overlays[i], true);
   }
#endif

#ifdef HAVE_MENU
#ifdef HAVE_MENU_WIDGETS
   if (video_info->widgets_inited)
      menu_widgets_frame(video_info);
#endif
#endif

   if (msg && *msg)
   {
      d3d9_set_viewports(d3d->dev, &screen_vp);
      d3d9_begin_scene(d3d->dev);
      font_driver_render_msg(video_info, NULL, msg, NULL);
      d3d9_end_scene(d3d->dev);
   }

   d3d9_update_title(video_info);
   d3d9_swap(d3d, d3d->dev);

   return true;
}