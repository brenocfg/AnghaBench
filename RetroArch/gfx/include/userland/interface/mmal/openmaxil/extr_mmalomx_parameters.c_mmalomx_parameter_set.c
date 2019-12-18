#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_18__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_35__ {int /*<<< orphan*/  eColorSpace; int /*<<< orphan*/  nPortIndex; } ;
struct TYPE_34__ {int nSize; int /*<<< orphan*/  nPFrames; int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; int /*<<< orphan*/  nPortIndex; } ;
struct TYPE_33__ {int nSize; int /*<<< orphan*/  nPFrames; int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; int /*<<< orphan*/  nPortIndex; } ;
struct TYPE_32__ {int nSize; int /*<<< orphan*/  nPFrames; int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; int /*<<< orphan*/  nPortIndex; } ;
struct TYPE_25__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_30__ {int /*<<< orphan*/  color_space; TYPE_17__ par; } ;
struct TYPE_31__ {TYPE_4__ video; } ;
struct TYPE_29__ {int nSize; int /*<<< orphan*/  nU32; int /*<<< orphan*/  nPortIndex; } ;
struct TYPE_27__ {int /*<<< orphan*/  nU32; } ;
struct TYPE_28__ {TYPE_1__ common; } ;
struct TYPE_26__ {TYPE_15__* format; } ;
struct TYPE_24__ {TYPE_5__* es; } ;
struct TYPE_23__ {int /*<<< orphan*/  no_cropping; TYPE_18__* mmal; TYPE_2__ format_param; } ;
struct TYPE_22__ {int /*<<< orphan*/  nY; int /*<<< orphan*/  nX; int /*<<< orphan*/  nPortIndex; } ;
struct TYPE_21__ {int /*<<< orphan*/  bEnabled; int /*<<< orphan*/  nPortIndex; } ;
struct TYPE_20__ {TYPE_3__ common; } ;
typedef  TYPE_6__ OMX_VIDEO_PARAM_MPEG4TYPE ;
typedef  TYPE_7__ OMX_VIDEO_PARAM_H263TYPE ;
typedef  TYPE_8__ OMX_VIDEO_PARAM_AVCTYPE ;
typedef  int OMX_U32 ;
typedef  scalar_t__ OMX_PTR ;
typedef  TYPE_9__ OMX_PARAM_COLORSPACETYPE ;
typedef  int OMX_INDEXTYPE ;
typedef  TYPE_10__ OMX_FORMAT_PARAM_TYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_11__ OMX_CONFIG_PORTBOOLEANTYPE ;
typedef  TYPE_12__ OMX_CONFIG_POINTTYPE ;
typedef  TYPE_13__ MMALOMX_PORT_T ;
typedef  int /*<<< orphan*/  MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_ErrorNotImplemented ; 
#define  OMX_IndexParamAudioAac 140 
#define  OMX_IndexParamAudioDdp 139 
#define  OMX_IndexParamAudioMp3 138 
#define  OMX_IndexParamAudioPcm 137 
#define  OMX_IndexParamBrcmPixelAspectRatio 136 
#define  OMX_IndexParamBrcmVideoCroppingDisable 135 
#define  OMX_IndexParamColorSpace 134 
#define  OMX_IndexParamVideoAvc 133 
#define  OMX_IndexParamVideoH263 132 
#define  OMX_IndexParamVideoMpeg2 131 
#define  OMX_IndexParamVideoMpeg4 130 
#define  OMX_IndexParamVideoRv 129 
#define  OMX_IndexParamVideoWmv 128 
 int /*<<< orphan*/  OMX_PARAM_U32TYPE ; 
 int /*<<< orphan*/  PARAM_GET_PORT (TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmal_port_format_commit (TYPE_18__*) ; 
 int /*<<< orphan*/  mmal_rational_simplify (TYPE_17__*) ; 
 int /*<<< orphan*/  mmalil_error_to_omx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_omx_audio_param_index_to_coding (int) ; 
 int /*<<< orphan*/  mmalil_omx_audio_param_to_format (TYPE_15__*,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  mmalil_omx_color_space_to_mmal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalomx_parameter_set_xlat (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  mmalomx_set_video_param (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nU32 ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OMX_ERRORTYPE mmalomx_parameter_set(MMALOMX_COMPONENT_T *component,
   OMX_INDEXTYPE nParamIndex, OMX_PTR pParam)
{
   MMALOMX_PORT_T *port = NULL;

   switch(nParamIndex)
   {
   /* All OMX_IndexParamVideo parameters are only partially implemented */
   case OMX_IndexParamVideoAvc:
      {
         OMX_VIDEO_PARAM_AVCTYPE *param = (OMX_VIDEO_PARAM_AVCTYPE *)pParam;
         PARAM_GET_PORT(port, component, param->nPortIndex);
         if (param->nSize < sizeof(*param))
            return OMX_ErrorBadParameter;
         return mmalomx_set_video_param(port, param->eProfile, param->eLevel,
            param->nPFrames + 1);
      }
   case OMX_IndexParamVideoMpeg4:
      {
         OMX_VIDEO_PARAM_MPEG4TYPE *param = (OMX_VIDEO_PARAM_MPEG4TYPE *)pParam;
         PARAM_GET_PORT(port, component, param->nPortIndex);
         if (param->nSize < sizeof(*param))
            return OMX_ErrorBadParameter;
         return mmalomx_set_video_param(port, param->eProfile, param->eLevel,
            param->nPFrames + 1);
      }
   case OMX_IndexParamVideoH263:
      {
         OMX_VIDEO_PARAM_H263TYPE *param = (OMX_VIDEO_PARAM_H263TYPE *)pParam;
         PARAM_GET_PORT(port, component, param->nPortIndex);
         if (param->nSize < sizeof(*param))
            return OMX_ErrorBadParameter;
         return mmalomx_set_video_param(port, param->eProfile, param->eLevel,
            param->nPFrames + 1);
      }
   case OMX_IndexParamVideoMpeg2:
   case OMX_IndexParamVideoWmv:
   case OMX_IndexParamVideoRv:
      {
         OMX_FORMAT_PARAM_TYPE *param = (OMX_FORMAT_PARAM_TYPE *)pParam;
         OMX_U32 offset = offsetof(OMX_PARAM_U32TYPE, nU32);
         PARAM_GET_PORT(port, component, param->common.nPortIndex);
         if (param->common.nSize > sizeof(port->format_param) ||
             param->common.nSize < offset)
            return OMX_ErrorBadParameter;
         memcpy(&port->format_param.common.nU32, &param->common.nU32,
                param->common.nSize - offset);
         return OMX_ErrorNone;
      }
   case OMX_IndexParamAudioPcm:
   case OMX_IndexParamAudioAac:
   case OMX_IndexParamAudioMp3:
   case OMX_IndexParamAudioDdp:
      {
         OMX_FORMAT_PARAM_TYPE *param = (OMX_FORMAT_PARAM_TYPE *)pParam;
         OMX_U32 offset = offsetof(OMX_PARAM_U32TYPE, nU32);
         PARAM_GET_PORT(port, component, param->common.nPortIndex);
         if (param->common.nSize > sizeof(port->format_param) ||
             param->common.nSize < offset)
            return OMX_ErrorBadParameter;
         memcpy(&port->format_param.common.nU32, &param->common.nU32,
                param->common.nSize - offset);
         mmalil_omx_audio_param_to_format(port->mmal->format,
            mmalil_omx_audio_param_index_to_coding(nParamIndex), param);
         mmal_port_format_commit(port->mmal);
         return OMX_ErrorNone;
      }
   case OMX_IndexParamBrcmPixelAspectRatio:
      {
         OMX_CONFIG_POINTTYPE *param = (OMX_CONFIG_POINTTYPE *)pParam;
         PARAM_GET_PORT(port, component, param->nPortIndex);
         port->mmal->format->es->video.par.num = param->nX;
         port->mmal->format->es->video.par.den = param->nY;
         mmal_rational_simplify(&port->mmal->format->es->video.par);
         return mmalil_error_to_omx(mmal_port_format_commit(port->mmal));
      }
   case OMX_IndexParamColorSpace:
      {
         OMX_PARAM_COLORSPACETYPE *param = (OMX_PARAM_COLORSPACETYPE *)pParam;
         PARAM_GET_PORT(port, component, param->nPortIndex);
         port->mmal->format->es->video.color_space = mmalil_omx_color_space_to_mmal(param->eColorSpace);
         return mmalil_error_to_omx(mmal_port_format_commit(port->mmal));
      }
   case OMX_IndexParamBrcmVideoCroppingDisable:
      {
         OMX_CONFIG_PORTBOOLEANTYPE *param = (OMX_CONFIG_PORTBOOLEANTYPE *)pParam;
         PARAM_GET_PORT(port, component, param->nPortIndex);
         port->no_cropping = param->bEnabled;
         return OMX_ErrorNone;
      }
   default:
      return mmalomx_parameter_set_xlat(component, nParamIndex, pParam);
   }

   return OMX_ErrorNotImplemented;
}