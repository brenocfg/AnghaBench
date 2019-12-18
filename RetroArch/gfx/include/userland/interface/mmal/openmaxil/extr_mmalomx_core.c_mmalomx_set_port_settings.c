#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_19__ {int /*<<< orphan*/  eEncoding; } ;
struct TYPE_26__ {scalar_t__ eCompressionFormat; scalar_t__ nFrameHeight; scalar_t__ nSliceHeight; int /*<<< orphan*/  nStride; void* nFrameWidth; int /*<<< orphan*/  eColorFormat; } ;
struct TYPE_21__ {scalar_t__ eCompressionFormat; scalar_t__ nFrameHeight; scalar_t__ nSliceHeight; int /*<<< orphan*/  xFramerate; int /*<<< orphan*/  nStride; void* nFrameWidth; int /*<<< orphan*/  nBitrate; int /*<<< orphan*/  eColorFormat; } ;
struct TYPE_27__ {TYPE_1__ audio; TYPE_8__ image; TYPE_3__ video; } ;
struct TYPE_25__ {void* encoding; TYPE_6__* es; int /*<<< orphan*/  bitrate; scalar_t__ encoding_variant; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {scalar_t__ height; void* width; } ;
struct TYPE_22__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_23__ {scalar_t__ height; TYPE_2__ crop; void* width; TYPE_4__ frame_rate; } ;
struct TYPE_24__ {TYPE_5__ video; } ;
struct TYPE_18__ {int /*<<< orphan*/  format_changed; int /*<<< orphan*/  no_cropping; TYPE_11__* mmal; } ;
struct TYPE_17__ {scalar_t__ buffer_size_min; scalar_t__ buffer_size; int /*<<< orphan*/  buffer_num; TYPE_7__* format; } ;
struct TYPE_16__ {scalar_t__ eDomain; scalar_t__ nBufferSize; int /*<<< orphan*/  nBufferCountActual; TYPE_9__ format; } ;
typedef  TYPE_10__ OMX_PARAM_PORTDEFINITIONTYPE ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_11__ MMAL_PORT_T ;
typedef  TYPE_12__ MMALOMX_PORT_T ;

/* Variables and functions */
 void* MMAL_ENCODING_UNKNOWN ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ OMX_IMAGE_CodingUnused ; 
 scalar_t__ OMX_PortDomainAudio ; 
 scalar_t__ OMX_PortDomainImage ; 
 scalar_t__ OMX_PortDomainVideo ; 
 scalar_t__ OMX_VIDEO_CodingUnused ; 
 void* mmal_encoding_stride_to_width (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_format_commit (TYPE_11__*) ; 
 void* mmalil_omx_audio_coding_to_encoding (int /*<<< orphan*/ ) ; 
 void* mmalil_omx_color_format_to_encoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_omx_domain_to_es_type (scalar_t__) ; 
 void* mmalil_omx_image_coding_to_encoding (scalar_t__) ; 
 void* mmalil_omx_video_coding_to_encoding (scalar_t__) ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_set_port_settings(MMALOMX_PORT_T *mmalomx_port,
   OMX_PARAM_PORTDEFINITIONTYPE *def)
{
   MMAL_PORT_T *port = mmalomx_port->mmal;
   uint32_t buffer_size_min = port->buffer_size_min;
   MMAL_STATUS_T status;

   port->format->type = mmalil_omx_domain_to_es_type(def->eDomain);
   port->format->encoding_variant = 0;

   if(def->eDomain == OMX_PortDomainVideo)
   {
      if (def->format.video.eCompressionFormat != OMX_VIDEO_CodingUnused)
         port->format->encoding = mmalil_omx_video_coding_to_encoding(def->format.video.eCompressionFormat);
      else
         port->format->encoding = mmalil_omx_color_format_to_encoding(def->format.video.eColorFormat);

      port->format->bitrate = def->format.video.nBitrate;
      port->format->es->video.width = def->format.video.nFrameWidth;
      if (!mmalomx_port->no_cropping)
         port->format->es->video.crop.width = port->format->es->video.width;
      if (mmal_encoding_stride_to_width(port->format->encoding, def->format.video.nStride))
         port->format->es->video.width =
            mmal_encoding_stride_to_width(port->format->encoding, def->format.video.nStride);
      port->format->es->video.height = def->format.video.nFrameHeight;
      if (!mmalomx_port->no_cropping)
         port->format->es->video.crop.height = port->format->es->video.height;
      if (def->format.video.nSliceHeight > def->format.video.nFrameHeight)
         port->format->es->video.height = def->format.video.nSliceHeight;
      port->format->es->video.frame_rate.num = def->format.video.xFramerate;
      port->format->es->video.frame_rate.den = (1<<16);
   }
   else if(def->eDomain == OMX_PortDomainImage)
   {
      if (def->format.image.eCompressionFormat != OMX_IMAGE_CodingUnused)
         port->format->encoding = mmalil_omx_image_coding_to_encoding(def->format.image.eCompressionFormat);
      else
         port->format->encoding = mmalil_omx_color_format_to_encoding(def->format.image.eColorFormat);

      port->format->es->video.width = def->format.image.nFrameWidth;
      if (!mmalomx_port->no_cropping)
         port->format->es->video.crop.width = port->format->es->video.width;
      if (mmal_encoding_stride_to_width(port->format->encoding, def->format.image.nStride))
         port->format->es->video.width =
            mmal_encoding_stride_to_width(port->format->encoding, def->format.image.nStride);
      port->format->es->video.height = def->format.image.nFrameHeight;
      if (!mmalomx_port->no_cropping)
         port->format->es->video.crop.height = port->format->es->video.height;
      if (def->format.image.nSliceHeight > def->format.image.nFrameHeight)
         port->format->es->video.height = def->format.image.nSliceHeight;
   }
   else if(def->eDomain == OMX_PortDomainAudio)
   {
      port->format->encoding = mmalil_omx_audio_coding_to_encoding(def->format.audio.eEncoding);
   }
   else
   {
      port->format->encoding = MMAL_ENCODING_UNKNOWN;
   }

   port->buffer_num = def->nBufferCountActual;
   port->buffer_size = def->nBufferSize;
   if (port->buffer_size < port->buffer_size_min)
      port->buffer_size = port->buffer_size_min;

   status = mmal_port_format_commit(port);
   if (status != MMAL_SUCCESS)
      return status;

   /* Acknowledge any ongoing port format changed event */
   mmalomx_port->format_changed = MMAL_FALSE;

   /* The minimum buffer size only changes when the format significantly changes
    * and in that case we want to advertise the new requirement to the client. */
   if (port->buffer_size_min != buffer_size_min)
      port->buffer_size = port->buffer_size_min;

   return MMAL_SUCCESS;
}