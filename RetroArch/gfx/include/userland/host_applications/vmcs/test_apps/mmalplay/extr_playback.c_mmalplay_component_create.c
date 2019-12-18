#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_25__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {void* time_setup; TYPE_2__* comp; int /*<<< orphan*/  name; } ;
struct TYPE_31__ {char* component_video_decoder; char* component_splitter; char* component_video_render; char* component_video_converter; char* component_video_scheduler; char* component_audio_decoder; char* component_audio_render; char* component_container_reader; int /*<<< orphan*/  output_uri; } ;
struct TYPE_34__ {size_t component_num; TYPE_1__ options; int /*<<< orphan*/  uri; scalar_t__ is_still_image; TYPE_4__* component; } ;
struct TYPE_33__ {TYPE_25__* control; } ;
struct TYPE_32__ {void* userdata; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMALPLAY_T ;
typedef  TYPE_4__ MMALPLAY_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_AUDIO_DECODER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_AUDIO_RENDERER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CONTAINER_READER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CONTAINER_WRITER ; 
 char* MMAL_COMPONENT_DEFAULT_IMAGE_DECODER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_SCHEDULER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_SPLITTER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_CONVERTER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_DECODER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER ; 
 size_t MMAL_COUNTOF (TYPE_4__*) ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_create (char const*,TYPE_2__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_component_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_port_enable (TYPE_25__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalplay_bh_control_cb ; 
 int /*<<< orphan*/  mmalplay_setup_audio_decoder (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmalplay_setup_audio_render (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmalplay_setup_container_reader (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalplay_setup_container_writer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalplay_setup_splitter (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmalplay_setup_video_converter (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmalplay_setup_video_decoder (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmalplay_setup_video_render (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmalplay_setup_video_scheduler (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 void* vcos_getmicrosecs () ; 
 int /*<<< orphan*/  vcos_safe_strcpy (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_COMPONENT_T *mmalplay_component_create(MMALPLAY_T *ctx,
   const char *name, MMAL_STATUS_T *status)
{
   MMALPLAY_COMPONENT_T *component = &ctx->component[ctx->component_num];
   const char *component_name = name;

   LOG_TRACE("%p, %s", ctx, name);

   if (ctx->component_num >= MMAL_COUNTOF(ctx->component))
   {
      *status = MMAL_ENOSPC;
      return NULL;
   }

   /* Decide whether we want an image decoder instead of a video_decoder */
   if (ctx->is_still_image &&
       !strcmp(name, MMAL_COMPONENT_DEFAULT_VIDEO_DECODER) && !ctx->options.component_video_decoder)
      ctx->options.component_video_decoder = MMAL_COMPONENT_DEFAULT_IMAGE_DECODER;

   /* Override name if requested by the user */
   if (!strcmp(name, MMAL_COMPONENT_DEFAULT_VIDEO_DECODER) && ctx->options.component_video_decoder)
      component_name = ctx->options.component_video_decoder;
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_SPLITTER) && ctx->options.component_splitter)
      component_name = ctx->options.component_splitter;
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER) && ctx->options.component_video_render)
      component_name = ctx->options.component_video_render;
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_VIDEO_CONVERTER) && ctx->options.component_video_converter)
      component_name = ctx->options.component_video_converter;
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_SCHEDULER) && ctx->options.component_video_scheduler)
      component_name = ctx->options.component_video_scheduler;
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_AUDIO_DECODER) && ctx->options.component_audio_decoder)
      component_name = ctx->options.component_audio_decoder;
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_AUDIO_RENDERER) && ctx->options.component_audio_render)
      component_name = ctx->options.component_audio_render;
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_CONTAINER_READER) && ctx->options.component_container_reader)
      component_name = ctx->options.component_container_reader;

   component->comp = NULL;
   vcos_safe_strcpy(component->name, component_name, sizeof(component->name), 0);
   component->time_setup = vcos_getmicrosecs();

   /* Create the component */
   *status = mmal_component_create(component_name, &component->comp);
   if(*status != MMAL_SUCCESS)
   {
      LOG_ERROR("couldn't create %s", component_name);
      goto error;
   }

   if (!strcmp(name, MMAL_COMPONENT_DEFAULT_CONTAINER_READER))
      *status = mmalplay_setup_container_reader(ctx, component->comp, ctx->uri);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_CONTAINER_WRITER))
      *status = mmalplay_setup_container_writer(ctx, component->comp, ctx->options.output_uri);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_VIDEO_DECODER))
      *status = mmalplay_setup_video_decoder(ctx, component->comp);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_SPLITTER))
      *status = mmalplay_setup_splitter(ctx, component->comp);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_VIDEO_CONVERTER))
      *status = mmalplay_setup_video_converter(ctx, component->comp);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER))
      *status = mmalplay_setup_video_render(ctx, component->comp);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_SCHEDULER))
      *status = mmalplay_setup_video_scheduler(ctx, component->comp);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_AUDIO_DECODER))
      *status = mmalplay_setup_audio_decoder(ctx, component->comp);
   else if (!strcmp(name, MMAL_COMPONENT_DEFAULT_AUDIO_RENDERER))
      *status = mmalplay_setup_audio_render(ctx, component->comp);

   if (*status != MMAL_SUCCESS)
      goto error;

   /* Enable component */
   *status = mmal_component_enable(component->comp);
   if(*status)
   {
      LOG_ERROR("%s couldn't be enabled", component_name);
      goto error;
   }

   /* Enable control port. The callback specified here is the function which
    * will be called when an empty buffer header comes back to the port. */
   component->comp->control->userdata = (void *)ctx;
   *status = mmal_port_enable(component->comp->control, mmalplay_bh_control_cb);
   if (*status)
   {
      LOG_ERROR("control port couldn't be enabled");
      goto error;
   }

   component->time_setup = vcos_getmicrosecs() - component->time_setup;
   ctx->component_num++;
   return component->comp;

 error:
   component->time_setup = vcos_getmicrosecs() - component->time_setup;
   if (component->comp)
      mmal_component_destroy(component->comp);
   return NULL;
}