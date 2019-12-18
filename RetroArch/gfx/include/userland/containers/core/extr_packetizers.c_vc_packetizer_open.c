#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ VC_PACKETIZER_T ;
struct TYPE_13__ {int /*<<< orphan*/  time; int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ VC_PACKETIZER_PRIVATE_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_14__ {int /*<<< orphan*/  codec_variant; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_3__ VC_CONTAINER_ES_FORMAT_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  bytestream_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc_container_format_copy (TYPE_3__*,TYPE_3__*,scalar_t__) ; 
 void* vc_container_format_create (scalar_t__) ; 
 int /*<<< orphan*/  vc_container_time_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vc_packetizer_close (TYPE_1__*) ; 
 scalar_t__ vc_packetizer_load (TYPE_1__*) ; 

VC_PACKETIZER_T *vc_packetizer_open( VC_CONTAINER_ES_FORMAT_T *in,
   VC_CONTAINER_FOURCC_T out_variant, VC_CONTAINER_STATUS_T *p_status )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_PACKETIZER_T *p_ctx = 0;

   /* Allocate our context before trying out the different packetizers */
   p_ctx = malloc( sizeof(*p_ctx) + sizeof(*p_ctx->priv));
   if(!p_ctx) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(p_ctx, 0, sizeof(*p_ctx) + sizeof(*p_ctx->priv));
   p_ctx->priv = (VC_PACKETIZER_PRIVATE_T *)(p_ctx + 1);
   bytestream_init( &p_ctx->priv->stream );

   p_ctx->in = vc_container_format_create(in->extradata_size);
   if(!p_ctx->in) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   p_ctx->out = vc_container_format_create(in->extradata_size);
   if(!p_ctx->out) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }

   vc_container_format_copy( p_ctx->in, in, in->extradata_size );
   p_ctx->in->extradata_size = 0;
   vc_container_format_copy( p_ctx->out, p_ctx->in, in->extradata_size );
   p_ctx->in->extradata_size = in->extradata_size;
   p_ctx->out->extradata = p_ctx->in->extradata;
   p_ctx->out->extradata_size = p_ctx->in->extradata_size;
   p_ctx->out->codec_variant = out_variant;

   vc_container_time_init(&p_ctx->priv->time, 1000000);

   status = vc_packetizer_load(p_ctx);
   if(status != VC_CONTAINER_SUCCESS)
      goto error;

 end:
   if(p_status) *p_status = status;
   return p_ctx;

 error:
   if(p_ctx) vc_packetizer_close(p_ctx);
   p_ctx = NULL;
   goto end;
}