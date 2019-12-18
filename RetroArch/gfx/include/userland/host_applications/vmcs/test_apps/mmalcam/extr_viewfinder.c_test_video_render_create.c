#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_24__ {scalar_t__ opaque; TYPE_1__ display_area; int /*<<< orphan*/  layer; } ;
struct TYPE_23__ {TYPE_4__** input; int /*<<< orphan*/  input_num; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_22__ {int set; TYPE_12__ hdr; TYPE_1__ dest_rect; scalar_t__ fullscreen; int /*<<< orphan*/  layer; } ;
struct TYPE_18__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int member_1; TYPE_12__ hdr; TYPE_2__ member_0; } ;
struct TYPE_20__ {TYPE_3__* format; } ;
struct TYPE_19__ {int /*<<< orphan*/  encoding; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  TYPE_5__ MMAL_PARAMETER_BOOLEAN_T ;
typedef  TYPE_6__ MMAL_DISPLAYREGION_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMALCAM_BEHAVIOUR_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  LOG_INFO (char*) ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER ; 
 int MMAL_DISPLAY_SET_DEST_RECT ; 
 int MMAL_DISPLAY_SET_FULLSCREEN ; 
 int MMAL_DISPLAY_SET_LAYER ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENCODING_OPAQUE ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_DISPLAYREGION ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ enable_zero_copy () ; 
 int /*<<< orphan*/  mmal_component_create (int /*<<< orphan*/ ,TYPE_7__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_7__*) ; 
 int /*<<< orphan*/  mmal_component_enable (TYPE_7__*) ; 
 int /*<<< orphan*/  mmal_port_parameter_set (TYPE_4__*,TYPE_12__*) ; 

__attribute__((used)) static MMAL_COMPONENT_T *test_video_render_create(MMALCAM_BEHAVIOUR_T *behaviour, MMAL_STATUS_T *status)
{
   MMAL_COMPONENT_T *render = 0;
   MMAL_PORT_T *render_port = NULL;

   *status = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER, &render);
   if(*status != MMAL_SUCCESS)
   {
      LOG_ERROR("couldn't create video render");
      goto error;
   }
   if(!render->input_num)
   {
      LOG_ERROR("video render doesn't have input ports");
      *status = MMAL_EINVAL;
      goto error;
   }

   render_port = render->input[0];

   /* Give higher priority to the overlay layer */
   MMAL_DISPLAYREGION_T param;
   param.hdr.id = MMAL_PARAMETER_DISPLAYREGION;
   param.hdr.size = sizeof(MMAL_DISPLAYREGION_T);
   param.set = MMAL_DISPLAY_SET_LAYER;
   param.layer = behaviour->layer;
   if (behaviour->display_area.width && behaviour->display_area.height)
   {
      param.set |= MMAL_DISPLAY_SET_DEST_RECT | MMAL_DISPLAY_SET_FULLSCREEN;
      param.fullscreen = 0;
      param.dest_rect = behaviour->display_area;
   }
   *status = mmal_port_parameter_set( render_port, &param.hdr );
   if (*status != MMAL_SUCCESS && *status != MMAL_ENOSYS)
   {
      LOG_ERROR("could not set video render display properties (%u)", *status);
      goto error;
   }

   if (enable_zero_copy())
   {
      MMAL_PARAMETER_BOOLEAN_T param_zc =
         {{MMAL_PARAMETER_ZERO_COPY, sizeof(MMAL_PARAMETER_BOOLEAN_T)}, 1};
      *status = mmal_port_parameter_set(render_port, &param_zc.hdr);
      if (*status != MMAL_SUCCESS && *status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on render input");
         goto error;
      }
      LOG_INFO("enabled zero copy on render");
   }

   if (behaviour->opaque)
   {
      render_port->format->encoding = MMAL_ENCODING_OPAQUE;
   }

   /* Enable component */
   *status = mmal_component_enable(render);
   if(*status)
   {
      LOG_ERROR("video render component couldn't be enabled (%u)", *status);
      goto error;
   }

   return render;

 error:
   if(render) mmal_component_destroy(render);
   return 0;
}