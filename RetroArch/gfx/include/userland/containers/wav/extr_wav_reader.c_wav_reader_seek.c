#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_15__ {TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_MODE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAGS_T ;
struct TYPE_16__ {int data_size; int position; scalar_t__ data_offset; scalar_t__ frame_data_left; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {TYPE_4__* format; } ;
struct TYPE_13__ {int bitrate; TYPE_3__* type; } ;
struct TYPE_11__ {int block_align; } ;
struct TYPE_12__ {TYPE_2__ audio; } ;
struct TYPE_10__ {TYPE_7__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T wav_reader_seek( VC_CONTAINER_T *p_ctx, int64_t *p_offset,
   VC_CONTAINER_SEEK_MODE_T mode, VC_CONTAINER_SEEK_FLAGS_T flags)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   int64_t position;
   VC_CONTAINER_PARAM_UNUSED(mode);
   VC_CONTAINER_PARAM_UNUSED(flags);

   position = *p_offset * p_ctx->tracks[0]->format->bitrate / 8000000;
   if(p_ctx->tracks[0]->format->type->audio.block_align)
      position = position / p_ctx->tracks[0]->format->type->audio.block_align *
         p_ctx->tracks[0]->format->type->audio.block_align;
   if(position > module->data_size) position = module->data_size;

   module->position = position;
   module->frame_data_left = 0;

   if(position >= module->data_size) return VC_CONTAINER_ERROR_EOS;
   return SEEK(p_ctx, module->data_offset + position);
}