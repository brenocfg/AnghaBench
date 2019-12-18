#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ current_time ;
struct TYPE_10__ {int duration; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {int size; int dts; int pts; int buffer_size; char* data; int /*<<< orphan*/  flags; scalar_t__ track; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
struct TYPE_12__ {int sent; int timestamp; int seek; TYPE_2__* pass; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_9__ {int len; int data; struct TYPE_9__* next; } ;
struct TYPE_8__ {TYPE_5__* module; } ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T qsynth_reader_read( VC_CONTAINER_T *p_ctx,
                                              VC_CONTAINER_PACKET_T *packet,
                                              uint32_t flags )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;

   if(module->pass)
   {
      packet->size = module->pass->len - module->sent;
      packet->dts = packet->pts = 0;
      packet->track = 0;
      packet->flags = module->sent ? 0 : VC_CONTAINER_PACKET_FLAG_FRAME_START;
   }
   else
   {
      if(module->timestamp > p_ctx->duration)
         return VC_CONTAINER_ERROR_EOS;

      packet->size = 5;
      packet->dts = packet->pts = module->timestamp;
      packet->track = 0;
      packet->flags = VC_CONTAINER_PACKET_FLAG_FRAME;
   }

   if(flags & VC_CONTAINER_READ_FLAG_SKIP)
   {
      if(module->pass)
      {
         module->pass = module->pass->next;
         module->sent = 0;
      }
      else
      {
         // if we're playing then we can't really skip, but have to simulate a seek instead
         module->seek = 1;
         module->timestamp += 40;
      }

      return VC_CONTAINER_SUCCESS;
   }

   if(flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   // read frame into packet->data
   if(module->pass)
   {
      uint32_t copy = MIN(packet->size, packet->buffer_size);
      memcpy(packet->data, module->pass->data + module->sent, copy);
      packet->size = copy;

      if((module->sent += copy) == module->pass->len)
      {
         module->pass = module->pass->next;
         module->sent = 0;
         packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_END;
      }
   }
   else
   {
      if(packet->buffer_size < packet->size)
         return VC_CONTAINER_ERROR_BUFFER_TOO_SMALL;

      if(module->seek)
      {
         uint32_t current_time = module->timestamp / 1000;

         packet->data[0] = 'S';
         packet->data[1] = (uint8_t)((current_time >> 24) & 0xFF);
         packet->data[2] = (uint8_t)((current_time >> 16) & 0xFF);
         packet->data[3] = (uint8_t)((current_time >>  8) & 0xFF);
         packet->data[4] = (uint8_t)((current_time      ) & 0xFF);
         module->seek = 0;
      }
      else
      {
         packet->data[0] = 'P';
         packet->data[1] = 0;
         packet->data[2] = 0;
         packet->data[3] = 0;
         packet->data[4] = 40;
         module->timestamp += 40 * 1000;
      }
   }

   return VC_CONTAINER_SUCCESS;
}