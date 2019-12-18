#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  eFormat; } ;
struct TYPE_22__ {int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; } ;
struct TYPE_21__ {int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; } ;
struct TYPE_20__ {int /*<<< orphan*/  bForceRoundingTypeToZero; int /*<<< orphan*/  bPLUSPTYPEAllowed; int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; } ;
struct TYPE_24__ {TYPE_7__ wmv; TYPE_6__ avc; TYPE_5__ mpeg4; TYPE_4__ h263; } ;
struct TYPE_25__ {TYPE_13__* mmal; TYPE_8__ format_param; } ;
struct TYPE_17__ {int num; int den; } ;
struct TYPE_18__ {int width; int height; TYPE_1__ frame_rate; } ;
struct TYPE_19__ {TYPE_2__ video; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; TYPE_10__* format; } ;
struct TYPE_15__ {int role; TYPE_9__* ports; int /*<<< orphan*/  registry_id; } ;
struct TYPE_14__ {int type; int bitrate; TYPE_3__* es; scalar_t__ encoding; } ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  scalar_t__ MMAL_FOURCC_T ;
typedef  int MMAL_ES_TYPE_T ;
typedef  TYPE_10__ MMAL_ES_FORMAT_T ;
typedef  int MMALOMX_ROLE_T ;
typedef  TYPE_11__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,char const*) ; 
#define  MMALOMX_ROLE_VIDEO_DECODER_AVC 135 
#define  MMALOMX_ROLE_VIDEO_DECODER_H263 134 
#define  MMALOMX_ROLE_VIDEO_DECODER_MPEG4 133 
#define  MMALOMX_ROLE_VIDEO_DECODER_WMV 132 
#define  MMALOMX_ROLE_VIDEO_ENCODER_AVC 131 
#define  MMALOMX_ROLE_VIDEO_ENCODER_H263 130 
#define  MMALOMX_ROLE_VIDEO_ENCODER_MPEG4 129 
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 int MMAL_ES_TYPE_UNKNOWN ; 
#define  MMAL_ES_TYPE_VIDEO 128 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_ErrorUnsupportedSetting ; 
 int /*<<< orphan*/  OMX_FALSE ; 
 int /*<<< orphan*/  OMX_TRUE ; 
 int /*<<< orphan*/  OMX_VIDEO_AVCLevel1 ; 
 int /*<<< orphan*/  OMX_VIDEO_AVCProfileBaseline ; 
 int /*<<< orphan*/  OMX_VIDEO_H263Level10 ; 
 int /*<<< orphan*/  OMX_VIDEO_H263ProfileBaseline ; 
 int /*<<< orphan*/  OMX_VIDEO_MPEG4Level1 ; 
 int /*<<< orphan*/  OMX_VIDEO_MPEG4ProfileSimple ; 
 int /*<<< orphan*/  OMX_VIDEO_WMVFormat9 ; 
 scalar_t__ mmal_port_format_commit (TYPE_13__*) ; 
 int /*<<< orphan*/  mmalomx_format_encoding_from_role (int const,scalar_t__*,int*,unsigned int*) ; 
 int /*<<< orphan*/  mmalomx_registry_component_supports_role (int /*<<< orphan*/ ,int const) ; 
 int mmalomx_role_from_name (char const*) ; 

OMX_ERRORTYPE mmalomx_role_set(MMALOMX_COMPONENT_T *component, const char *name)
{
   const MMALOMX_ROLE_T role = mmalomx_role_from_name(name);
   MMAL_FOURCC_T encoding = MMAL_ENCODING_UNKNOWN;
   MMAL_ES_TYPE_T es_type = MMAL_ES_TYPE_UNKNOWN;
   unsigned int port;
   MMAL_ES_FORMAT_T *format;

   if (!role || !mmalomx_registry_component_supports_role(component->registry_id, role))
      return OMX_ErrorUnsupportedSetting;

   component->role = role;

   mmalomx_format_encoding_from_role(role, &encoding, &es_type, &port);
   if (encoding == MMAL_ENCODING_UNKNOWN)
      return OMX_ErrorNone;

   format = component->ports[port].mmal->format;
   format->type = es_type;
   format->encoding = encoding;
   format->bitrate = 64000;
   switch (es_type)
   {
   case MMAL_ES_TYPE_VIDEO:
      format->es->video.width = 176;
      format->es->video.height = 144;
      format->es->video.frame_rate.num = 15;
      format->es->video.frame_rate.den = 1;
      break;
   default:
      break;
   }

   switch (role)
   {
   case MMALOMX_ROLE_VIDEO_DECODER_H263:
   case MMALOMX_ROLE_VIDEO_ENCODER_H263:
      component->ports[port].format_param.h263.eProfile = OMX_VIDEO_H263ProfileBaseline;
      component->ports[port].format_param.h263.eLevel = OMX_VIDEO_H263Level10;
      component->ports[port].format_param.h263.bPLUSPTYPEAllowed = OMX_FALSE;
      component->ports[port].format_param.h263.bForceRoundingTypeToZero = OMX_TRUE;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_MPEG4:
   case MMALOMX_ROLE_VIDEO_ENCODER_MPEG4:
      component->ports[port].format_param.mpeg4.eProfile = OMX_VIDEO_MPEG4ProfileSimple;
      component->ports[port].format_param.mpeg4.eLevel = OMX_VIDEO_MPEG4Level1;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_AVC:
   case MMALOMX_ROLE_VIDEO_ENCODER_AVC:
      component->ports[port].format_param.avc.eProfile = OMX_VIDEO_AVCProfileBaseline;
      component->ports[port].format_param.avc.eLevel = OMX_VIDEO_AVCLevel1;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_WMV:
      component->ports[port].format_param.wmv.eFormat = OMX_VIDEO_WMVFormat9;
      break;
   default:
      break;
   }

   if (mmal_port_format_commit(component->ports[port].mmal) != MMAL_SUCCESS)
      LOG_ERROR("failed to commit format to %s for role %s",
                component->ports[port].mmal->name, name);

   return OMX_ErrorNone;
}