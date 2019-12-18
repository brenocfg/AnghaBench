#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  long long int64_t ;
typedef  int /*<<< orphan*/  dummy ;
struct TYPE_18__ {long long duration; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_19__ {TYPE_5__* track; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_20__ {int num_frames; int constant_c5; int constant_4; int constant_c; int framerate; int /*<<< orphan*/  struct_b; } ;
struct TYPE_17__ {TYPE_4__* format; } ;
struct TYPE_16__ {int extradata_size; TYPE_3__* type; int /*<<< orphan*/  extradata; } ;
struct TYPE_14__ {int frame_rate_num; int frame_rate_den; void* width; void* height; } ;
struct TYPE_15__ {TYPE_2__ video; } ;
struct TYPE_13__ {TYPE_7__* module; } ;
typedef  TYPE_8__ RCV_FILE_HEADER_T ;

/* Variables and functions */
 int LI24 (int*) ; 
 void* LI32 (int*) ; 
 int PEEK_BYTES (TYPE_6__*,int*,int) ; 
 int /*<<< orphan*/  SKIP_BYTES (TYPE_6__*,int) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_6__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rcv_read_header(VC_CONTAINER_T *p_ctx)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   RCV_FILE_HEADER_T header;
   uint8_t dummy[36];

   if(PEEK_BYTES(p_ctx, dummy, sizeof(dummy)) != sizeof(dummy)) return VC_CONTAINER_ERROR_EOS;

   header.num_frames = LI24(dummy);
   header.constant_c5 = dummy[3];
   header.constant_4 = LI32(dummy+4);

   // extradata is just struct_c from the header
   memcpy(module->extradata, dummy+8, 4);
   module->track->format->extradata = module->extradata;
   module->track->format->extradata_size = 4;

   module->track->format->type->video.height = LI32(dummy+12);
   module->track->format->type->video.width = LI32(dummy+16);

   header.constant_c = LI32(dummy+20);
   memcpy(header.struct_b, dummy+24, 8);
   header.framerate = LI32(dummy+32);

   if(header.constant_c5 != 0xc5 || header.constant_4 != 0x4 || header.constant_c != 0xc)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   if(header.framerate != 0 && header.framerate != 0xffffffffUL)
   {
      module->track->format->type->video.frame_rate_num = header.framerate;
      module->track->format->type->video.frame_rate_den = 1;
   }

   // fill in general information
   if(header.num_frames != (1<<24)-1 && header.framerate != 0 && header.framerate != 0xffffffffUL)
      p_ctx->duration = ((int64_t) header.num_frames * 1000000LL) / (int64_t) header.framerate;

   // we're happy that this is an rcv file
   SKIP_BYTES(p_ctx, sizeof(dummy));

   return STREAM_STATUS(p_ctx);
}