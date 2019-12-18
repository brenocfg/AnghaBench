#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {size_t output_num; TYPE_2__** output; int /*<<< orphan*/  name; int /*<<< orphan*/  control; } ;
struct TYPE_7__ {TYPE_1__* format; } ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,char const*,...) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ES_TYPE_VIDEO ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_util_port_set_uri (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static MMAL_STATUS_T svp_setup_reader(MMAL_COMPONENT_T *reader, const char *uri,
                                      MMAL_PORT_T **video_port)
{
   MMAL_STATUS_T st;
   uint32_t track;

   st = mmal_util_port_set_uri(reader->control, uri);
   if (st != MMAL_SUCCESS)
   {
      LOG_ERROR("%s: couldn't open uri %s", reader->name, uri);
      return st;
   }

   /* Find a video track */
   for (track = 0; track < reader->output_num; track++)
   {
      if (reader->output[track]->format->type == MMAL_ES_TYPE_VIDEO)
      {
         break;
      }
   }

   if (track == reader->output_num)
   {
      LOG_ERROR("%s: no video track", uri);
      return MMAL_EINVAL;
   }

   *video_port = reader->output[track];
   return MMAL_SUCCESS;
}