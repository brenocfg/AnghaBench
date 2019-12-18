#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {TYPE_5__* out; TYPE_2__* in; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_PACKETIZER_T ;
struct TYPE_10__ {int length_size; } ;
typedef  TYPE_4__ VC_PACKETIZER_MODULE_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {int* extradata; unsigned int extradata_size; } ;
struct TYPE_8__ {int* extradata; int extradata_size; } ;
struct TYPE_7__ {TYPE_4__* module; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 scalar_t__ vc_container_format_extradata_alloc (TYPE_5__*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avc1_packetizer_codecconfig( VC_PACKETIZER_T *p_ctx )
{
   VC_PACKETIZER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;
   uint8_t *out, *extra = p_ctx->in->extradata + 5;
   uint8_t *extra_end = extra + p_ctx->in->extradata_size - 5;
   unsigned int i, j, nal_size, out_size = 0;

   if (p_ctx->in->extradata_size <= 5 ||
       p_ctx->in->extradata[0] != 1 /* configurationVersion */)
      return VC_CONTAINER_ERROR_FORMAT_INVALID;

   status = vc_container_format_extradata_alloc(p_ctx->out, p_ctx->in->extradata_size);
   if (status != VC_CONTAINER_SUCCESS)
      return status;

   out = p_ctx->out->extradata;
   module->length_size = (*(p_ctx->in->extradata + 4) & 0x3) + 1;

   for (i = 0; i < 2 && extra < extra_end - 1; i++)
   {
      j = *(extra++) & (!i ? 0x1F : 0xFF);
      for (; j > 0 && extra < extra_end - 2; j--)
      {
         nal_size = (extra[0] << 8) | extra[1]; extra += 2;
         if (extra + nal_size > extra_end)
         {
            extra = extra_end;
            break;
         }

         out[0] = out[1] = out[2] = 0; out[3] = 1;
         memcpy(out + 4, extra, nal_size);
         out += nal_size + 4; extra += nal_size;
         out_size += nal_size + 4;
      }
   }

   p_ctx->out->extradata_size = out_size;
   return VC_CONTAINER_SUCCESS;
}