#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_36__ {int /*<<< orphan*/  value; } ;
struct TYPE_35__ {int /*<<< orphan*/  value; } ;
struct TYPE_34__ {int id; } ;
struct TYPE_33__ {int /*<<< orphan*/  value; } ;
struct TYPE_32__ {int /*<<< orphan*/  value; } ;
struct TYPE_31__ {TYPE_3__* priv; } ;
struct TYPE_30__ {TYPE_2__* clock; } ;
struct TYPE_29__ {int /*<<< orphan*/  (* event_cb ) (TYPE_4__*,TYPE_12__*) ;int /*<<< orphan*/  buffer_info_reporting; } ;
struct TYPE_28__ {int /*<<< orphan*/  request_threshold; int /*<<< orphan*/  discont_threshold; int /*<<< orphan*/  update_threshold; int /*<<< orphan*/  media_time; int /*<<< orphan*/  scale; int /*<<< orphan*/  enable; } ;
struct TYPE_27__ {TYPE_1__ data; int /*<<< orphan*/  id; } ;
struct TYPE_26__ {int /*<<< orphan*/  enable; } ;
struct TYPE_25__ {int /*<<< orphan*/  value; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  TYPE_5__ MMAL_PARAMETER_RATIONAL_T ;
typedef  TYPE_6__ MMAL_PARAMETER_INT64_T ;
typedef  TYPE_7__ MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_8__ MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD_T ;
typedef  TYPE_9__ MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD_T ;
typedef  TYPE_10__ MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD_T ;
typedef  TYPE_11__ MMAL_PARAMETER_BOOLEAN_T ;
typedef  TYPE_12__ MMAL_CLOCK_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int) ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_ACTIVE ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_DISCONT_THRESHOLD ; 
 TYPE_12__ MMAL_CLOCK_EVENT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_INVALID ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_REFERENCE ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_REQUEST_THRESHOLD ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_SCALE ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_TIME ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_UPDATE_THRESHOLD ; 
 scalar_t__ MMAL_ENOSYS ; 
#define  MMAL_PARAMETER_CLOCK_ACTIVE 135 
#define  MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD 134 
#define  MMAL_PARAMETER_CLOCK_ENABLE_BUFFER_INFO 133 
#define  MMAL_PARAMETER_CLOCK_REFERENCE 132 
#define  MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD 131 
#define  MMAL_PARAMETER_CLOCK_SCALE 130 
#define  MMAL_PARAMETER_CLOCK_TIME 129 
#define  MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD 128 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_port_clock_active_set (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_clock_discont_threshold_set (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_clock_media_time_set (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_clock_reference_set (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_clock_request_threshold_set (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_clock_scale_set (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_clock_update_threshold_set (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_12__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_parameter_set(MMAL_PORT_T *port, const MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_STATUS_T status = MMAL_SUCCESS;
   MMAL_CLOCK_EVENT_T event = MMAL_CLOCK_EVENT_INIT(MMAL_CLOCK_EVENT_INVALID);

   switch (param->id)
   {
      case MMAL_PARAMETER_CLOCK_REFERENCE:
      {
         const MMAL_PARAMETER_BOOLEAN_T *p = (const MMAL_PARAMETER_BOOLEAN_T*)param;
         status = mmal_port_clock_reference_set(port, p->enable);
         event.id = MMAL_CLOCK_EVENT_REFERENCE;
         event.data.enable = p->enable;
      }
      break;
      case MMAL_PARAMETER_CLOCK_ACTIVE:
      {
         const MMAL_PARAMETER_BOOLEAN_T *p = (const MMAL_PARAMETER_BOOLEAN_T*)param;
         status = mmal_port_clock_active_set(port, p->enable);
         event.id = MMAL_CLOCK_EVENT_ACTIVE;
         event.data.enable = p->enable;
      }
      break;
      case MMAL_PARAMETER_CLOCK_SCALE:
      {
         const MMAL_PARAMETER_RATIONAL_T *p = (const MMAL_PARAMETER_RATIONAL_T*)param;
         status = mmal_port_clock_scale_set(port, p->value);
         event.id = MMAL_CLOCK_EVENT_SCALE;
         event.data.scale = p->value;
      }
      break;
      case MMAL_PARAMETER_CLOCK_TIME:
      {
         const MMAL_PARAMETER_INT64_T *p = (const MMAL_PARAMETER_INT64_T*)param;
         status = mmal_port_clock_media_time_set(port, p->value);
         event.id = MMAL_CLOCK_EVENT_TIME;
         event.data.media_time = p->value;
      }
      break;
      case MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD:
      {
         const MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD_T *p = (const MMAL_PARAMETER_CLOCK_UPDATE_THRESHOLD_T *)param;
         status = mmal_port_clock_update_threshold_set(port, &p->value);
         event.id = MMAL_CLOCK_EVENT_UPDATE_THRESHOLD;
         event.data.update_threshold = p->value;
      }
      break;
      case MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD:
      {
         const MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD_T *p = (const MMAL_PARAMETER_CLOCK_DISCONT_THRESHOLD_T *)param;
         status = mmal_port_clock_discont_threshold_set(port, &p->value);
         event.id = MMAL_CLOCK_EVENT_DISCONT_THRESHOLD;
         event.data.discont_threshold = p->value;
      }
      break;
      case MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD:
      {
         const MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD_T *p = (const MMAL_PARAMETER_CLOCK_REQUEST_THRESHOLD_T *)param;
         status = mmal_port_clock_request_threshold_set(port, &p->value);
         event.id = MMAL_CLOCK_EVENT_REQUEST_THRESHOLD;
         event.data.request_threshold = p->value;
      }
      break;
      case MMAL_PARAMETER_CLOCK_ENABLE_BUFFER_INFO:
      {
         const MMAL_PARAMETER_BOOLEAN_T *p = (const MMAL_PARAMETER_BOOLEAN_T*)param;
         port->priv->clock->buffer_info_reporting = p->enable;
         return MMAL_SUCCESS;
      }
      default:
         LOG_ERROR("unsupported clock parameter 0x%x", param->id);
         return MMAL_ENOSYS;
   }

   /* Notify the component */
   if (port->priv->clock->event_cb && status == MMAL_SUCCESS)
      port->priv->clock->event_cb(port, &event);

   return status;
}