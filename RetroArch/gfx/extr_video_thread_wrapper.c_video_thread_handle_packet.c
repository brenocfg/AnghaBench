#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vp ;
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_26__ {int within_thread; } ;
struct video_viewport {int /*<<< orphan*/  full_height; int /*<<< orphan*/  full_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_24__ {int alpha_mods; float* alpha_mod; int /*<<< orphan*/ * driver_data; TYPE_8__* poke; TYPE_5__* overlay; TYPE_13__* driver; TYPE_1__ frame; int /*<<< orphan*/  is_idle; int /*<<< orphan*/  read_vp; struct video_viewport vp; int /*<<< orphan*/  input_data; int /*<<< orphan*/  input; int /*<<< orphan*/  info; } ;
typedef  TYPE_14__ thread_video_t ;
struct TYPE_21__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* method ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  return_value; } ;
struct TYPE_20__ {int /*<<< orphan*/  is_threaded; int /*<<< orphan*/  api; int /*<<< orphan*/  font_size; int /*<<< orphan*/  font_path; int /*<<< orphan*/  video_data; int /*<<< orphan*/  font_handle; int /*<<< orphan*/  font_driver; int /*<<< orphan*/  (* method ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  return_value; } ;
struct TYPE_34__ {int /*<<< orphan*/  params; int /*<<< orphan*/  msg; } ;
struct TYPE_32__ {int /*<<< orphan*/  smooth; int /*<<< orphan*/  index; } ;
struct TYPE_31__ {int /*<<< orphan*/  fullscreen; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_29__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  index; } ;
struct TYPE_28__ {int num; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {int /*<<< orphan*/  path; int /*<<< orphan*/  type; } ;
struct TYPE_22__ {int b; TYPE_11__ custom_command; TYPE_10__ font_init; TYPE_9__ osd_message; int /*<<< orphan*/  i; TYPE_7__ filtering; TYPE_6__ new_mode; TYPE_4__ rect; TYPE_3__ image; TYPE_2__ set_shader; scalar_t__ v; } ;
struct TYPE_25__ {int type; TYPE_12__ data; } ;
typedef  TYPE_15__ thread_packet_t ;
struct TYPE_33__ {int /*<<< orphan*/  (* set_osd_msg ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_aspect_ratio ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_filtering ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_video_mode ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_30__ {int (* load ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* full_screen ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* vertex_geom ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* tex_geom ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable ) (int /*<<< orphan*/ *,int) ;} ;
struct TYPE_23__ {int (* read_viewport ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int (* set_shader ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* alive ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* viewport_info ) (int /*<<< orphan*/ *,struct video_viewport*) ;int /*<<< orphan*/  (* set_rotation ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* init ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  CMD_ALIVE 145 
#define  CMD_CUSTOM_COMMAND 144 
#define  CMD_FONT_INIT 143 
#define  CMD_FREE 142 
#define  CMD_INIT 141 
#define  CMD_OVERLAY_ENABLE 140 
#define  CMD_OVERLAY_FULL_SCREEN 139 
#define  CMD_OVERLAY_LOAD 138 
#define  CMD_OVERLAY_TEX_GEOM 137 
#define  CMD_OVERLAY_VERTEX_GEOM 136 
#define  CMD_POKE_SET_ASPECT_RATIO 135 
#define  CMD_POKE_SET_FILTERING 134 
#define  CMD_POKE_SET_OSD_MSG 133 
#define  CMD_POKE_SET_VIDEO_MODE 132 
#define  CMD_READ_VIEWPORT 131 
#define  CMD_SET_ROTATION 130 
#define  CMD_SET_SHADER 129 
#define  CMD_VIDEO_NONE 128 
 scalar_t__ realloc (float*,int) ; 
 int /*<<< orphan*/  string_is_equal_fast (struct video_viewport*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub10 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct video_viewport*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,struct video_viewport*) ; 
 int stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub7 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  video_driver_build_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_thread_reply (TYPE_14__*,TYPE_15__*) ; 

__attribute__((used)) static bool video_thread_handle_packet(
      thread_video_t *thr,
      const thread_packet_t *incoming)
{
#ifdef HAVE_OVERLAY
   unsigned i;
#endif
   thread_packet_t pkt = *incoming;
   bool            ret = false;

   switch (pkt.type)
   {
      case CMD_INIT:
         thr->driver_data = thr->driver->init(&thr->info,
               thr->input, thr->input_data);
         pkt.data.b = (thr->driver_data != NULL);
         thr->driver->viewport_info(thr->driver_data, &thr->vp);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_FREE:
         if (thr->driver_data)
         {
            if (thr->driver && thr->driver->free)
               thr->driver->free(thr->driver_data);
         }
         thr->driver_data = NULL;
         video_thread_reply(thr, &pkt);
         return true;

      case CMD_SET_ROTATION:
         if (thr->driver && thr->driver->set_rotation)
            thr->driver->set_rotation(thr->driver_data, pkt.data.i);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_READ_VIEWPORT:
      {
         struct video_viewport vp;

         vp.x                     = 0;
         vp.y                     = 0;
         vp.width                 = 0;
         vp.height                = 0;
         vp.full_width            = 0;
         vp.full_height           = 0;

         thr->driver->viewport_info(thr->driver_data, &vp);

         if (string_is_equal_fast(&vp, &thr->read_vp, sizeof(vp)))
         {
            /* We can read safely
             *
             * read_viewport() in GL driver calls
             * 'cached frame render' to be able to read from
             * back buffer.
             *
             * This means frame() callback in threaded wrapper will
             * be called from this thread, causing a timeout, and
             * no frame to be rendered.
             *
             * To avoid this, set a flag so wrapper can see if
             * it's called in this "special" way. */
            thr->frame.within_thread = true;

            if (thr->driver->read_viewport)
               ret = thr->driver->read_viewport(thr->driver_data,
                     (uint8_t*)pkt.data.v, thr->is_idle);

            pkt.data.b = ret;
            thr->frame.within_thread = false;
         }
         else
         {
            /* Viewport dimensions changed right after main
             * thread read the async value. Cannot read safely. */
            pkt.data.b = false;
         }
         video_thread_reply(thr, &pkt);
         break;
      }

      case CMD_SET_SHADER:
         if (thr->driver && thr->driver->set_shader)
            ret = thr->driver->set_shader(thr->driver_data,
                     pkt.data.set_shader.type,
                     pkt.data.set_shader.path);

         pkt.data.b = ret;
         video_thread_reply(thr, &pkt);
         break;

      case CMD_ALIVE:
         if (thr->driver && thr->driver->alive)
            ret = thr->driver->alive(thr->driver_data);

         pkt.data.b = ret;
         video_thread_reply(thr, &pkt);
         break;

#ifdef HAVE_OVERLAY
      case CMD_OVERLAY_ENABLE:
         if (thr->overlay && thr->overlay->enable)
            thr->overlay->enable(thr->driver_data, pkt.data.b);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_OVERLAY_LOAD:
         {
            float *tmp_alpha_mod = NULL;

            if (thr->overlay && thr->overlay->load)
               ret = thr->overlay->load(thr->driver_data,
                     pkt.data.image.data,
                     pkt.data.image.num);

            pkt.data.b         = ret;
            thr->alpha_mods    = pkt.data.image.num;
            tmp_alpha_mod      = (float*)realloc(thr->alpha_mod,
                  thr->alpha_mods * sizeof(float));

            if (tmp_alpha_mod)
               thr->alpha_mod  = tmp_alpha_mod;

            /* Avoid temporary garbage data. */
            for (i = 0; i < thr->alpha_mods; i++)
               thr->alpha_mod[i] = 1.0f;

            video_thread_reply(thr, &pkt);
         }
         break;

      case CMD_OVERLAY_TEX_GEOM:
         if (thr->overlay && thr->overlay->tex_geom)
            thr->overlay->tex_geom(thr->driver_data,
                  pkt.data.rect.index,
                  pkt.data.rect.x,
                  pkt.data.rect.y,
                  pkt.data.rect.w,
                  pkt.data.rect.h);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_OVERLAY_VERTEX_GEOM:
         if (thr->overlay && thr->overlay->vertex_geom)
            thr->overlay->vertex_geom(thr->driver_data,
                  pkt.data.rect.index,
                  pkt.data.rect.x,
                  pkt.data.rect.y,
                  pkt.data.rect.w,
                  pkt.data.rect.h);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_OVERLAY_FULL_SCREEN:
         if (thr->overlay && thr->overlay->full_screen)
            thr->overlay->full_screen(thr->driver_data,
                  pkt.data.b);
         video_thread_reply(thr, &pkt);
         break;
#endif

      case CMD_POKE_SET_VIDEO_MODE:
         if (thr->poke && thr->poke->set_video_mode)
            thr->poke->set_video_mode(thr->driver_data,
                  pkt.data.new_mode.width,
                  pkt.data.new_mode.height,
                  pkt.data.new_mode.fullscreen);
         video_thread_reply(thr, &pkt);
         break;
      case CMD_POKE_SET_FILTERING:
         if (thr->poke && thr->poke->set_filtering)
            thr->poke->set_filtering(thr->driver_data,
                  pkt.data.filtering.index,
                  pkt.data.filtering.smooth);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_POKE_SET_ASPECT_RATIO:
         if (thr->poke && thr->poke->set_aspect_ratio)
            thr->poke->set_aspect_ratio(thr->driver_data,
                  pkt.data.i);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_POKE_SET_OSD_MSG:
         {
            video_frame_info_t video_info;
            video_driver_build_info(&video_info);
            if (thr->poke && thr->poke->set_osd_msg)
               thr->poke->set_osd_msg(thr->driver_data,
                     &video_info,
                     pkt.data.osd_message.msg,
                     &pkt.data.osd_message.params, NULL);
         }
         video_thread_reply(thr, &pkt);
         break;

      case CMD_FONT_INIT:
         if (pkt.data.font_init.method)
            pkt.data.font_init.return_value =
                  pkt.data.font_init.method
                  (pkt.data.font_init.font_driver,
                     pkt.data.font_init.font_handle,
                     pkt.data.font_init.video_data,
                     pkt.data.font_init.font_path,
                     pkt.data.font_init.font_size,
                     pkt.data.font_init.api,
                     pkt.data.font_init.is_threaded);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_CUSTOM_COMMAND:
         if (pkt.data.custom_command.method)
            pkt.data.custom_command.return_value =
                  pkt.data.custom_command.method
                  (pkt.data.custom_command.data);
         video_thread_reply(thr, &pkt);
         break;

      case CMD_VIDEO_NONE:
         /* Never reply on no command. Possible deadlock if
          * thread sends command right after frame update. */
         break;
      default:
         video_thread_reply(thr, &pkt);
         break;
   }

   return false;
}