#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  enum CodecID { ____Placeholder_CodecID } CodecID ;
struct TYPE_31__ {TYPE_14__* codec_context; int /*<<< orphan*/  picture; } ;
struct TYPE_30__ {TYPE_11__** output; TYPE_1__* priv; } ;
struct TYPE_29__ {TYPE_13__* format; TYPE_8__* component; } ;
struct TYPE_28__ {int /*<<< orphan*/  (* pf_set_format ) (TYPE_11__*) ;} ;
struct TYPE_26__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_27__ {TYPE_4__ video; } ;
struct TYPE_24__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_25__ {TYPE_2__ video; } ;
struct TYPE_23__ {TYPE_9__* module; } ;
struct TYPE_22__ {scalar_t__ pix_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  flags; scalar_t__ extradata; scalar_t__ extradata_size; } ;
struct TYPE_21__ {TYPE_3__* es; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; int /*<<< orphan*/  encoding; } ;
struct TYPE_20__ {TYPE_5__* es; int /*<<< orphan*/  encoding; } ;
struct TYPE_19__ {TYPE_6__* priv; TYPE_12__* format; } ;
struct TYPE_18__ {int capabilities; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_7__ MMAL_PORT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_T ;
typedef  TYPE_9__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_10__ AVCodec ;

/* Variables and functions */
 int CODEC_CAP_TRUNCATED ; 
 int /*<<< orphan*/  CODEC_FLAG_TRUNCATED ; 
 int CODEC_ID_NONE ; 
 scalar_t__ DEFAULT_HEIGHT ; 
 scalar_t__ DEFAULT_WIDTH ; 
 scalar_t__ FF_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  LOG_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  MMAL_EIO ; 
 int /*<<< orphan*/  MMAL_ENXIO ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ PIX_FMT_NONE ; 
 scalar_t__ PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  avcodec_alloc_frame () ; 
 TYPE_10__* avcodec_find_decoder (int) ; 
 scalar_t__ avcodec_open (TYPE_14__*,TYPE_10__*) ; 
 int encoding_to_codecid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmal_format_copy (TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  pixfmt_to_encoding (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*) ; 
 scalar_t__ vcos_calloc (int,scalar_t__,char*) ; 

__attribute__((used)) static MMAL_STATUS_T avcodec_input_port_set_format(MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   enum CodecID codec_id;
   AVCodec *codec;

   codec_id = encoding_to_codecid(port->format->encoding);
   if(codec_id == CODEC_ID_NONE ||
      !(codec = avcodec_find_decoder(codec_id)))
   {
      LOG_ERROR("ffmpeg codec id %d (for %4.4s) not recognized",
                codec_id, (char *)&port->format->encoding);
      return MMAL_ENXIO;
   }

   module->picture = avcodec_alloc_frame();

   module->codec_context->width  = port->format->es->video.width;
   module->codec_context->height  = port->format->es->video.height;
   module->codec_context->extradata_size  = port->format->extradata_size;
   module->codec_context->extradata =
      vcos_calloc(1, port->format->extradata_size + FF_INPUT_BUFFER_PADDING_SIZE,
                  "avcodec extradata");
   if(module->codec_context->extradata)
      memcpy(module->codec_context->extradata, port->format->extradata,
             port->format->extradata_size);

   if (codec->capabilities & CODEC_CAP_TRUNCATED)
      module->codec_context->flags |= CODEC_FLAG_TRUNCATED;

   if (avcodec_open(module->codec_context, codec) < 0)
   {
      LOG_ERROR("could not open codec");
      return MMAL_EIO;
   }

   /* Set a default format */
   if (module->codec_context->pix_fmt == PIX_FMT_NONE)
      module->codec_context->pix_fmt = PIX_FMT_YUV420P;

   /* Copy format to output */
   LOG_DEBUG("avcodec output format %i (%ix%i)", module->codec_context->pix_fmt,
             module->codec_context->width, module->codec_context->height);
   port->format->es->video.width = module->codec_context->width;
   port->format->es->video.height = module->codec_context->height;
   mmal_format_copy(component->output[0]->format, port->format);
   component->output[0]->format->encoding = pixfmt_to_encoding(module->codec_context->pix_fmt);
   if (!component->output[0]->format->es->video.width)
      component->output[0]->format->es->video.width = DEFAULT_WIDTH;
   if (!component->output[0]->format->es->video.height)
      component->output[0]->format->es->video.height = DEFAULT_HEIGHT;

   component->output[0]->priv->pf_set_format(component->output[0]);

   return MMAL_SUCCESS;
}