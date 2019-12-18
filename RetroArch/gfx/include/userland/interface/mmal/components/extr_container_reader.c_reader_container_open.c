#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {unsigned int tracks_num; TYPE_2__** tracks; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  scalar_t__ VC_CONTAINER_ES_TYPE_T ;
struct TYPE_22__ {unsigned int ports; TYPE_6__* container; } ;
struct TYPE_21__ {unsigned int output_num; TYPE_5__** output; TYPE_1__* priv; } ;
struct TYPE_19__ {TYPE_11__* format; TYPE_4__* priv; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; } ;
struct TYPE_18__ {TYPE_3__* module; } ;
struct TYPE_17__ {unsigned int track; } ;
struct TYPE_16__ {TYPE_12__* format; scalar_t__ is_enabled; } ;
struct TYPE_15__ {TYPE_8__* module; } ;
struct TYPE_14__ {scalar_t__ es_type; int /*<<< orphan*/  codec; } ;
struct TYPE_13__ {scalar_t__ encoding; int /*<<< orphan*/  type; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 int /*<<< orphan*/  MMAL_ES_TYPE_UNKNOWN ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  READER_MIN_BUFFER_NUM ; 
 int /*<<< orphan*/  READER_MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  READER_RECOMMENDED_BUFFER_NUM ; 
 int /*<<< orphan*/  READER_RECOMMENDED_BUFFER_SIZE ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_SUBPICTURE ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ container_map_to_mmal_status (int /*<<< orphan*/ ) ; 
 scalar_t__ container_to_mmal_encoding (int /*<<< orphan*/ ) ; 
 scalar_t__ container_to_mmal_format (TYPE_11__*,TYPE_12__*) ; 
 TYPE_6__* vc_container_open_reader (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T reader_container_open(MMAL_COMPONENT_T *component, const char *uri)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   VC_CONTAINER_STATUS_T cstatus;
   VC_CONTAINER_T *container;
   unsigned int i, port, track;

   /* Open container */
   module->container = container =
      vc_container_open_reader(uri, &cstatus, 0, 0);
   if(!container)
   {
     LOG_ERROR("error opening file %s (%i)", uri, cstatus);
     return container_map_to_mmal_status(cstatus);
   }

   /* Disable all tracks */
   for(track = 0; track < container->tracks_num; track++)
      container->tracks[track]->is_enabled = 0;

   /* Fill-in the ports */
   for(i = 0, port = 0; i < component->output_num; i++)
   {
      VC_CONTAINER_ES_TYPE_T type = VC_CONTAINER_ES_TYPE_VIDEO;
      if(i == 1) type = VC_CONTAINER_ES_TYPE_AUDIO;
      if(i == 2) type = VC_CONTAINER_ES_TYPE_SUBPICTURE;

      /* Look for the first track with the specified type */
      for(track = 0; track < container->tracks_num; track++)
         if(container->tracks[track]->format->es_type == type)
            break;
      if(track == container->tracks_num)
         continue;

      if(container_to_mmal_encoding(container->tracks[track]->format->codec) == MMAL_ENCODING_UNKNOWN)
         continue;

      /* Set format of the port */
      if(container_to_mmal_format(component->output[port]->format,
                                  container->tracks[track]->format) != MMAL_SUCCESS)
         continue;

      component->output[port]->buffer_num_min = READER_MIN_BUFFER_NUM;
      component->output[port]->buffer_num_recommended = READER_RECOMMENDED_BUFFER_NUM;
      component->output[port]->buffer_size_min = READER_MIN_BUFFER_SIZE;
      component->output[port]->buffer_size_recommended = READER_RECOMMENDED_BUFFER_SIZE;
      component->output[port]->priv->module->track = track;

      /* We're done with this port */
      port++;
   }
   module->ports = port;

   /* Reset the left over ports */
   for(i = port; i < component->output_num; i++)
   {
      component->output[i]->format->type = MMAL_ES_TYPE_UNKNOWN;
      component->output[i]->format->encoding = MMAL_ENCODING_UNKNOWN;
   }

   return MMAL_SUCCESS;
}