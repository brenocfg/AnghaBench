#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  enum conversion { ____Placeholder_conversion } conversion ;
struct TYPE_20__ {int max_frame_size; TYPE_7__* priv; TYPE_6__* in; TYPE_3__* out; } ;
typedef  TYPE_8__ VC_PACKETIZER_T ;
struct TYPE_21__ {int conversion; int conversion_factor; int max_frame_size; unsigned int bytes_per_sample; unsigned int samples_per_frame; } ;
typedef  TYPE_9__ VC_PACKETIZER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_19__ {int /*<<< orphan*/  pf_reset; int /*<<< orphan*/  pf_packetize; int /*<<< orphan*/  pf_close; int /*<<< orphan*/  time; TYPE_9__* module; } ;
struct TYPE_18__ {scalar_t__ codec; TYPE_5__* type; } ;
struct TYPE_16__ {int block_align; int bits_per_sample; int channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_17__ {TYPE_4__ audio; } ;
struct TYPE_15__ {scalar_t__ codec_variant; scalar_t__ codec; TYPE_2__* type; } ;
struct TYPE_13__ {int bits_per_sample; int block_align; } ;
struct TYPE_14__ {TYPE_1__ audio; } ;

/* Variables and functions */
 int CONVERSION_NONE ; 
 int CONVERSION_U8_TO_S16L ; 
 int CONVERSION_UNKNOWN ; 
 int FACTOR_SHIFT ; 
 int FRAME_SIZE ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ VC_CONTAINER_CODEC_PCM_FLOAT_BE ; 
 scalar_t__ VC_CONTAINER_CODEC_PCM_FLOAT_LE ; 
 scalar_t__ VC_CONTAINER_CODEC_PCM_SIGNED_BE ; 
 scalar_t__ VC_CONTAINER_CODEC_PCM_SIGNED_LE ; 
 scalar_t__ VC_CONTAINER_CODEC_PCM_UNSIGNED_BE ; 
 scalar_t__ VC_CONTAINER_CODEC_PCM_UNSIGNED_LE ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ VC_FOURCC (char,char,char,char) ; 
 TYPE_9__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_packetizer_close ; 
 int /*<<< orphan*/  pcm_packetizer_packetize ; 
 int /*<<< orphan*/  pcm_packetizer_reset ; 
 int /*<<< orphan*/  vc_container_time_set_samplerate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

VC_CONTAINER_STATUS_T pcm_packetizer_open( VC_PACKETIZER_T *p_ctx )
{
   VC_PACKETIZER_MODULE_T *module;
   unsigned int bytes_per_sample = 0;
   enum conversion conversion = CONVERSION_NONE;

   if(p_ctx->in->codec != VC_CONTAINER_CODEC_PCM_UNSIGNED_BE &&
      p_ctx->in->codec != VC_CONTAINER_CODEC_PCM_UNSIGNED_LE &&
      p_ctx->in->codec != VC_CONTAINER_CODEC_PCM_SIGNED_BE &&
      p_ctx->in->codec != VC_CONTAINER_CODEC_PCM_SIGNED_LE &&
      p_ctx->in->codec != VC_CONTAINER_CODEC_PCM_FLOAT_BE &&
      p_ctx->in->codec != VC_CONTAINER_CODEC_PCM_FLOAT_LE)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   if(p_ctx->in->type->audio.block_align)
      bytes_per_sample = p_ctx->in->type->audio.block_align;
   else if(p_ctx->in->type->audio.bits_per_sample && p_ctx->in->type->audio.channels)
      bytes_per_sample = p_ctx->in->type->audio.bits_per_sample *
         p_ctx->in->type->audio.channels / 8;

   if(!bytes_per_sample)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Check if we support any potential conversion we've been asked to do */
   if(p_ctx->out->codec_variant)
      conversion = CONVERSION_UNKNOWN;
   if(p_ctx->out->codec_variant == VC_FOURCC('s','1','6','l') &&
      p_ctx->in->codec == VC_CONTAINER_CODEC_PCM_SIGNED_LE &&
      p_ctx->in->type->audio.bits_per_sample == 16)
      conversion = CONVERSION_NONE;
   if(p_ctx->out->codec_variant == VC_FOURCC('s','1','6','l') &&
      (p_ctx->in->codec == VC_CONTAINER_CODEC_PCM_UNSIGNED_LE ||
       p_ctx->in->codec == VC_CONTAINER_CODEC_PCM_UNSIGNED_BE) &&
      p_ctx->in->type->audio.bits_per_sample == 8)
      conversion = CONVERSION_U8_TO_S16L;
   if(conversion == CONVERSION_UNKNOWN)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   p_ctx->priv->module = module = malloc(sizeof(*module));
   if(!module)
      return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   memset(module, 0, sizeof(*module));
   module->conversion = conversion;
   module->conversion_factor = 1 << FACTOR_SHIFT;

   p_ctx->out->codec_variant = 0;
   if(conversion == CONVERSION_U8_TO_S16L)
   {
      module->conversion_factor = 2 << FACTOR_SHIFT;
      p_ctx->out->type->audio.bits_per_sample *= 2;
      p_ctx->out->type->audio.block_align *= 2;
      p_ctx->out->codec = VC_CONTAINER_CODEC_PCM_SIGNED_LE;
   }

   vc_container_time_set_samplerate(&p_ctx->priv->time, p_ctx->in->type->audio.sample_rate, 1);

   p_ctx->max_frame_size = FRAME_SIZE;
   module->max_frame_size = (FRAME_SIZE << FACTOR_SHIFT) / module->conversion_factor;
   module->bytes_per_sample = bytes_per_sample;
   module->samples_per_frame = module->max_frame_size / bytes_per_sample;
   p_ctx->priv->pf_close = pcm_packetizer_close;
   p_ctx->priv->pf_packetize = pcm_packetizer_packetize;
   p_ctx->priv->pf_reset = pcm_packetizer_reset;

   LOG_DEBUG(0, "using pcm audio packetizer");
   return VC_CONTAINER_SUCCESS;
}