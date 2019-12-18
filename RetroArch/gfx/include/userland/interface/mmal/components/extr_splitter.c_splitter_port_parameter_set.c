#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_14__ {unsigned int output_num; TYPE_2__** output; TYPE_1__** input; } ;
struct TYPE_13__ {int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; } ;
struct TYPE_12__ {int id; } ;
struct TYPE_11__ {int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; TYPE_6__* component; } ;
struct TYPE_10__ {void* buffer_size_recommended; void* buffer_size_min; void* buffer_num_recommended; void* buffer_num_min; } ;
struct TYPE_9__ {void* buffer_size_recommended; void* buffer_size_min; void* buffer_num_recommended; void* buffer_num_min; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_5__ MMAL_PARAMETER_BUFFER_REQUIREMENTS_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 void* MMAL_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MMAL_PARAMETER_BUFFER_REQUIREMENTS 128 
 int /*<<< orphan*/  MMAL_SUCCESS ; 

__attribute__((used)) static MMAL_STATUS_T splitter_port_parameter_set(MMAL_PORT_T *port, const MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_COMPONENT_T *component = port->component;
   unsigned int i;

   switch (param->id)
   {
   case MMAL_PARAMETER_BUFFER_REQUIREMENTS:
      {
         /* Propagate the requirements to all the ports */
         const MMAL_PARAMETER_BUFFER_REQUIREMENTS_T *req = (const MMAL_PARAMETER_BUFFER_REQUIREMENTS_T *)param;
         uint32_t buffer_num_min = MMAL_MAX(port->buffer_num_min, req->buffer_num_min);
         uint32_t buffer_num_recommended = MMAL_MAX(port->buffer_num_recommended, req->buffer_num_recommended);
         uint32_t buffer_size_min = MMAL_MAX(port->buffer_size_min, req->buffer_size_min);
         uint32_t buffer_size_recommended = MMAL_MAX(port->buffer_size_recommended, req->buffer_size_recommended);

         component->input[0]->buffer_num_min = buffer_num_min;
         component->input[0]->buffer_num_recommended = buffer_num_recommended;
         component->input[0]->buffer_size_min = buffer_size_min;
         component->input[0]->buffer_size_recommended = buffer_size_recommended;
         for (i = 0; i < component->output_num; i++)
         {
            component->output[i]->buffer_num_min = buffer_num_min;
            component->output[i]->buffer_num_recommended = buffer_num_recommended;
            component->output[i]->buffer_size_min = buffer_size_min;
            component->output[i]->buffer_size_recommended = buffer_size_recommended;
         }

      }
      return MMAL_SUCCESS;

   default:
      return MMAL_ENOSYS;
   }
}