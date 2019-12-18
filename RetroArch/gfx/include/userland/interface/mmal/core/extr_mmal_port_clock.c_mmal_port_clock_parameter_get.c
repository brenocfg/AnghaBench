#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  value; } ;
struct TYPE_21__ {int /*<<< orphan*/  value; } ;
struct TYPE_20__ {int /*<<< orphan*/  value; } ;
struct TYPE_19__ {int id; } ;
struct TYPE_18__ {int /*<<< orphan*/  value; } ;
struct TYPE_17__ {int /*<<< orphan*/  value; } ;
struct TYPE_16__ {int /*<<< orphan*/  buffer_info_reporting; int /*<<< orphan*/  clock; int /*<<< orphan*/  is_reference; } ;
struct TYPE_15__ {TYPE_1__* priv; } ;
struct TYPE_14__ {TYPE_3__* clock; } ;
struct TYPE_13__ {int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_CLOCK_T ;
typedef  TYPE_4__ MMAL_PARAMETER_RATIONAL_T ;
typedef  TYPE_5__ MMAL_PARAMETER_INT64_T ;
typedef  TYPE_6__ MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_7__ MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD_T ;
typedef  TYPE_8__ MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD_T ;
typedef  TYPE_9__ MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD_T ;
typedef  TYPE_10__ MMAL_PARAMETER_BOOLEAN_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int) ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
#define  MMAL_PARAMETER_CLOCK_ACTIVE 135 
#define  MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD 134 
#define  MMAL_PARAMETER_CLOCK_ENABLE_BUFFER_INFO 133 
#define  MMAL_PARAMETER_CLOCK_REFERENCE 132 
#define  MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD 131 
#define  MMAL_PARAMETER_CLOCK_SCALE 130 
#define  MMAL_PARAMETER_CLOCK_TIME 129 
#define  MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD 128 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_clock_discont_threshold_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_clock_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_clock_media_time_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_clock_request_threshold_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_clock_scale_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_clock_update_threshold_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_parameter_get(MMAL_PORT_T *port, MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_PORT_CLOCK_T *priv_clock = port->priv->clock;
   MMAL_STATUS_T status = MMAL_SUCCESS;

   switch (param->id)
   {
      case MMAL_PARAMETER_CLOCK_REFERENCE:
      {
         MMAL_PARAMETER_BOOLEAN_T *p = (MMAL_PARAMETER_BOOLEAN_T*)param;
         p->enable = priv_clock->is_reference;
      }
      break;
      case MMAL_PARAMETER_CLOCK_ACTIVE:
      {
         MMAL_PARAMETER_BOOLEAN_T *p = (MMAL_PARAMETER_BOOLEAN_T*)param;
         p->enable = mmal_clock_is_active(priv_clock->clock);
      }
      break;
      case MMAL_PARAMETER_CLOCK_SCALE:
      {
         MMAL_PARAMETER_RATIONAL_T *p = (MMAL_PARAMETER_RATIONAL_T*)param;
         p->value = mmal_clock_scale_get(priv_clock->clock);
      }
      break;
      case MMAL_PARAMETER_CLOCK_TIME:
      {
         MMAL_PARAMETER_INT64_T *p = (MMAL_PARAMETER_INT64_T*)param;
         p->value = mmal_clock_media_time_get(priv_clock->clock);
      }
      break;
      case MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD:
      {
         MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD_T *p = (MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD_T *)param;
         status = mmal_clock_update_threshold_get(priv_clock->clock, &p->value);
      }
      break;
      case MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD:
      {
         MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD_T *p = (MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD_T *)param;
         status = mmal_clock_discont_threshold_get(priv_clock->clock, &p->value);
      }
      break;
      case MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD:
      {
         MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD_T *p = (MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD_T *)param;
         status = mmal_clock_request_threshold_get(priv_clock->clock, &p->value);
      }
      break;
      case MMAL_PARAMETER_CLOCK_ENABLE_BUFFER_INFO:
      {
         MMAL_PARAMETER_BOOLEAN_T *p = (MMAL_PARAMETER_BOOLEAN_T*)param;
         p->enable = priv_clock->buffer_info_reporting;
      }
      break;
      default:
         LOG_ERROR("unsupported clock parameter 0x%x", param->id);
         return MMAL_ENOSYS;
   }

   return status;
}