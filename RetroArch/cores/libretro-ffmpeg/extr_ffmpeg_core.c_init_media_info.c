#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sample_rate; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct TYPE_6__ {double interpolate_fps; float height; float aspect; scalar_t__ width; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_5__ {float height; int /*<<< orphan*/  sample_aspect_ratio; scalar_t__ width; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASS_HINTING_LIGHT ; 
 TYPE_4__** actx ; 
 int /*<<< orphan*/  ass ; 
 int /*<<< orphan*/  ass_add_font (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__* ass_extra_data ; 
 int /*<<< orphan*/ * ass_extra_data_size ; 
 int /*<<< orphan*/  ass_library_init () ; 
 int /*<<< orphan*/  ass_msg_cb ; 
 int /*<<< orphan*/  ass_new_track (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_process_codec_private (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_render ; 
 int /*<<< orphan*/  ass_renderer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_set_extract_fonts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ass_set_fonts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ass_set_frame_size (int /*<<< orphan*/ ,scalar_t__,float) ; 
 int /*<<< orphan*/  ass_set_hinting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_set_message_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ass_track ; 
 TYPE_3__* attachments ; 
 unsigned int attachments_size ; 
 float av_q2d (int /*<<< orphan*/ ) ; 
 TYPE_2__ media ; 
 scalar_t__* sctx ; 
 scalar_t__ subtitle_streams_num ; 
 TYPE_1__* vctx ; 

__attribute__((used)) static bool init_media_info(void)
{
   if (actx[0])
      media.sample_rate = actx[0]->sample_rate;

   media.interpolate_fps = 60.0;

   if (vctx)
   {
      media.width  = vctx->width;
      media.height = vctx->height;
      media.aspect = (float)vctx->width *
         av_q2d(vctx->sample_aspect_ratio) / vctx->height;
   }

#ifdef HAVE_SSA
   if (sctx[0])
   {
      unsigned i;

      ass = ass_library_init();
      ass_set_message_cb(ass, ass_msg_cb, NULL);

      for (i = 0; i < attachments_size; i++)
         ass_add_font(ass, (char*)"",
               (char*)attachments[i].data, attachments[i].size);

      ass_render = ass_renderer_init(ass);
      ass_set_frame_size(ass_render, media.width, media.height);
      ass_set_extract_fonts(ass, true);
      ass_set_fonts(ass_render, NULL, NULL, 1, NULL, 1);
      ass_set_hinting(ass_render, ASS_HINTING_LIGHT);

      for (i = 0; i < (unsigned)subtitle_streams_num; i++)
      {
         ass_track[i] = ass_new_track(ass);
         ass_process_codec_private(ass_track[i], (char*)ass_extra_data[i],
               ass_extra_data_size[i]);
      }
   }
#endif

   return true;
}