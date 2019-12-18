#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_9__ {scalar_t__ offset; scalar_t__ current_offset; scalar_t__ bytes; } ;
typedef  TYPE_3__ VC_CONTAINER_BYTESTREAM_T ;
struct TYPE_7__ {int /*<<< orphan*/  (* pf_reset ) (TYPE_2__*) ;TYPE_3__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  bytestream_skip (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

VC_CONTAINER_STATUS_T vc_packetizer_reset( VC_PACKETIZER_T *p_ctx )
{
   VC_CONTAINER_BYTESTREAM_T *stream = &p_ctx->priv->stream;

   bytestream_skip( stream, stream->bytes - stream->current_offset - stream->offset );

   if (p_ctx->priv->pf_reset)
      return p_ctx->priv->pf_reset(p_ctx);
   else
      return VC_CONTAINER_SUCCESS;
}