#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; int /*<<< orphan*/  max_frame_size; TYPE_3__* in; int /*<<< orphan*/  out; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
typedef  int /*<<< orphan*/  VC_PACKETIZER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_7__ {scalar_t__ codec; } ;
struct TYPE_5__ {int /*<<< orphan*/  pf_reset; int /*<<< orphan*/  pf_packetize; int /*<<< orphan*/  pf_close; int /*<<< orphan*/ * module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAX_FRAME_SIZE ; 
 scalar_t__ VC_CONTAINER_CODEC_MP1V ; 
 scalar_t__ VC_CONTAINER_CODEC_MP2V ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpgv_packetizer_close ; 
 int /*<<< orphan*/  mpgv_packetizer_packetize ; 
 int /*<<< orphan*/  mpgv_packetizer_reset ; 
 int /*<<< orphan*/  vc_container_format_copy (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T mpgv_packetizer_open( VC_PACKETIZER_T *p_ctx )
{
   VC_PACKETIZER_MODULE_T *module;

   if(p_ctx->in->codec != VC_CONTAINER_CODEC_MP1V &&
      p_ctx->in->codec != VC_CONTAINER_CODEC_MP2V)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   p_ctx->priv->module = module = malloc(sizeof(*module));
   if(!module)
      return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   memset(module, 0, sizeof(*module));

   vc_container_format_copy( p_ctx->out, p_ctx->in, 0);
   p_ctx->max_frame_size = MAX_FRAME_SIZE;
   p_ctx->priv->pf_close = mpgv_packetizer_close;
   p_ctx->priv->pf_packetize = mpgv_packetizer_packetize;
   p_ctx->priv->pf_reset = mpgv_packetizer_reset;
   LOG_DEBUG(0, "using mpeg video packetizer");
   return VC_CONTAINER_SUCCESS;
}