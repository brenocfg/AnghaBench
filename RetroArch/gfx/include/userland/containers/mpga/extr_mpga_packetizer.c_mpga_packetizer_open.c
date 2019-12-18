#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv; int /*<<< orphan*/  max_frame_size; TYPE_4__* in; int /*<<< orphan*/  out; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
struct TYPE_10__ {int /*<<< orphan*/  pf_read_header; } ;
typedef  TYPE_3__ VC_PACKETIZER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {scalar_t__ codec; } ;
struct TYPE_8__ {int /*<<< orphan*/  pf_reset; int /*<<< orphan*/  pf_packetize; int /*<<< orphan*/  pf_close; TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAX_FRAME_SIZE ; 
 scalar_t__ VC_CONTAINER_CODEC_MP4A ; 
 scalar_t__ VC_CONTAINER_CODEC_MPGA ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  adts_read_header ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpga_packetizer_close ; 
 int /*<<< orphan*/  mpga_packetizer_packetize ; 
 int /*<<< orphan*/  mpga_packetizer_reset ; 
 int /*<<< orphan*/  mpga_read_header ; 
 int /*<<< orphan*/  vc_container_format_copy (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T mpga_packetizer_open( VC_PACKETIZER_T *p_ctx )
{
   VC_PACKETIZER_MODULE_T *module;

   if(p_ctx->in->codec != VC_CONTAINER_CODEC_MPGA &&
      p_ctx->in->codec != VC_CONTAINER_CODEC_MP4A)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   p_ctx->priv->module = module = malloc(sizeof(*module));
   if(!module)
      return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   memset(module, 0, sizeof(*module));

   if(p_ctx->in->codec == VC_CONTAINER_CODEC_MPGA)
      module->pf_read_header = mpga_read_header;
   else
      module->pf_read_header = adts_read_header;

   vc_container_format_copy( p_ctx->out, p_ctx->in, 0);
   p_ctx->max_frame_size = MAX_FRAME_SIZE;
   p_ctx->priv->pf_close = mpga_packetizer_close;
   p_ctx->priv->pf_packetize = mpga_packetizer_packetize;
   p_ctx->priv->pf_reset = mpga_packetizer_reset;
   LOG_DEBUG(0, "using mpeg audio packetizer");
   return VC_CONTAINER_SUCCESS;
}