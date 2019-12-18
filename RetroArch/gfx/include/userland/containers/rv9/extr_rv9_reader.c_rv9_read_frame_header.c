#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {int len; int num_segments; void* flags; void* sequence; void* timestamp; } ;
struct TYPE_10__ {int* data; int data_len; int frame_len; int type; TYPE_2__ hdr; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_7__ {TYPE_4__* module; } ;

/* Variables and functions */
 void* BI16 (int*) ; 
 void* BI32 (int*) ; 
 int FRAME_HEADER_LEN ; 
 int MAX_NUM_SEGMENTS ; 
 int READ_BYTES (TYPE_3__*,int*,int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rv9_read_frame_header(VC_CONTAINER_T *p_ctx)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   uint32_t seg_offset = (uint32_t) -1;
   uint8_t *buffer = module->data + FRAME_HEADER_LEN;

   if(READ_BYTES(p_ctx, module->data, FRAME_HEADER_LEN) != FRAME_HEADER_LEN) return VC_CONTAINER_ERROR_EOS;
   module->data_len = FRAME_HEADER_LEN;

   module->hdr.len = BI32(module->data);
   module->hdr.timestamp = BI32(module->data+4);
   module->hdr.sequence = BI16(module->data+8);
   module->hdr.flags = BI16(module->data+10);
   module->hdr.num_segments = BI32(module->data+16);

   module->frame_len = FRAME_HEADER_LEN + (module->hdr.num_segments * 8) + module->hdr.len;

   // if we have space, we store up the segments in memory so we can tell the frame
   // type, since most streams have their type byte as the first follow the segment information.
   // if we don't have space, then we just don't know the frame type, so will not emit timestamp
   // information as we don't know if it's reliable.
   if(module->hdr.num_segments <= MAX_NUM_SEGMENTS)
   {
      uint32_t i;

      if(READ_BYTES(p_ctx, buffer, 8*module->hdr.num_segments) != 8*module->hdr.num_segments) return VC_CONTAINER_ERROR_EOS;
      module->data_len += (module->hdr.num_segments * 8);

      for (i=0; i<module->hdr.num_segments; i++)
      {
         uint32_t valid_seg;
         uint32_t offset;

         valid_seg = BI32(buffer);
         offset = BI32(buffer+4);

         if (valid_seg && seg_offset > offset)
            seg_offset = offset;

         // this boolean field should have only 0 or 1 values
         if(valid_seg > 1) return VC_CONTAINER_ERROR_FORMAT_INVALID;

         buffer += 8;
      }
   }

   if(seg_offset == 0)
   {
      if (READ_BYTES(p_ctx, buffer, 1) != 1) return VC_CONTAINER_ERROR_EOS;
      module->data_len += 1;

      module->type = (*buffer >> 5) & 3;
   }
   else
      module->type = (uint8_t) -1;

   return VC_CONTAINER_SUCCESS;
}