#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  copy_output; scalar_t__ window; int /*<<< orphan*/  video_destination; scalar_t__ render_layer; } ;
struct TYPE_20__ {TYPE_2__ options; } ;
struct TYPE_19__ {TYPE_10__** input; int /*<<< orphan*/  name; int /*<<< orphan*/  input_num; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_14__ {int width; int height; unsigned int y; scalar_t__ x; } ;
struct TYPE_18__ {int set; TYPE_11__ hdr; scalar_t__ fullscreen; int /*<<< orphan*/  mode; TYPE_1__ dest_rect; int /*<<< orphan*/  display_num; scalar_t__ layer; } ;
struct TYPE_16__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int member_1; TYPE_11__ hdr; TYPE_3__ member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PARAMETER_BOOLEAN_T ;
typedef  TYPE_5__ MMAL_DISPLAYREGION_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;
typedef  TYPE_7__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_DISPLAY_MODE_LETTERBOX ; 
 int MMAL_DISPLAY_SET_DEST_RECT ; 
 int MMAL_DISPLAY_SET_FULLSCREEN ; 
 int MMAL_DISPLAY_SET_LAYER ; 
 int MMAL_DISPLAY_SET_MODE ; 
 int MMAL_DISPLAY_SET_NUM ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_DISPLAYREGION ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_port_parameter_set (TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  video_render_num ; 

__attribute__((used)) static MMAL_STATUS_T mmalplay_setup_video_render(MMALPLAY_T *ctx, MMAL_COMPONENT_T *render)
{
   MMAL_STATUS_T status = MMAL_EINVAL;
   unsigned int render_num;

   if(!render->input_num)
   {
      LOG_ERROR("%s doesn't have input ports", render->name);
      goto error;
   }

   render_num = video_render_num++;

   /* Give higher priority to the overlay layer */
   MMAL_DISPLAYREGION_T param;
   param.hdr.id = MMAL_PARAMETER_DISPLAYREGION;
   param.hdr.size = sizeof(MMAL_DISPLAYREGION_T);
   param.set = MMAL_DISPLAY_SET_LAYER|MMAL_DISPLAY_SET_NUM;
   param.layer = ctx->options.render_layer + 2;   /* Offset of two to put it above the Android UI layer */
   param.display_num = ctx->options.video_destination;
   if (ctx->options.window)
   {
      param.dest_rect.x = 0;
      param.dest_rect.width = 512;
      param.dest_rect.height = 256;
      param.dest_rect.y = param.dest_rect.height * render_num;
      param.mode = MMAL_DISPLAY_MODE_LETTERBOX;
      param.fullscreen = 0;
      param.set |= MMAL_DISPLAY_SET_DEST_RECT|MMAL_DISPLAY_SET_MODE|MMAL_DISPLAY_SET_FULLSCREEN;
   }
   status = mmal_port_parameter_set( render->input[0], &param.hdr );
   if(status != MMAL_SUCCESS && status != MMAL_ENOSYS)
   {
      LOG_ERROR("could not set video render layer on %s", render->input[0]->name);
      goto error;
   }

   /* Enable Zero Copy if requested. This needs to be sent before enabling the port. */
   if (!ctx->options.copy_output)
   {
      MMAL_PARAMETER_BOOLEAN_T param_zc =
         {{MMAL_PARAMETER_ZERO_COPY, sizeof(MMAL_PARAMETER_BOOLEAN_T)}, 1};
      status = mmal_port_parameter_set(render->input[0], &param_zc.hdr);
      if (status != MMAL_SUCCESS && status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on %s", render->input[0]->name);
         goto error;
      }
   }

   status = MMAL_SUCCESS;

 error:
   return status;
}