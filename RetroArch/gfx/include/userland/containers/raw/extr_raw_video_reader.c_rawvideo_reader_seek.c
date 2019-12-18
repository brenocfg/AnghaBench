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
typedef  int VC_CONTAINER_SEEK_FLAGS_T ;
struct TYPE_16__ {int frames; int block_size; int frame_header_size; int /*<<< orphan*/  status; scalar_t__ data_offset; scalar_t__ frame_header; scalar_t__ block_offset; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {TYPE_4__* format; } ;
struct TYPE_13__ {TYPE_3__* type; } ;
struct TYPE_11__ {int frame_rate_num; int frame_rate_den; } ;
struct TYPE_12__ {TYPE_2__ video; } ;
struct TYPE_10__ {TYPE_7__* module; } ;

/* Variables and functions */
 int INT64_C (int) ; 
 int /*<<< orphan*/  SEEK (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 int VC_CONTAINER_SEEK_FLAG_FORWARD ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rawvideo_reader_seek( VC_CONTAINER_T *ctx, int64_t *offset,
   VC_CONTAINER_SEEK_MODE_T mode, VC_CONTAINER_SEEK_FLAGS_T flags)
{
   VC_CONTAINER_MODULE_T *module = ctx->priv->module;
   VC_CONTAINER_PARAM_UNUSED(mode);

   module->frames = *offset *
      ctx->tracks[0]->format->type->video.frame_rate_num /
      ctx->tracks[0]->format->type->video.frame_rate_den / INT64_C(1000000);
   module->block_offset = 0;

   if ((flags & VC_CONTAINER_SEEK_FLAG_FORWARD) &&
      module->frames * INT64_C(1000000) *
         ctx->tracks[0]->format->type->video.frame_rate_den /
         ctx->tracks[0]->format->type->video.frame_rate_num < *offset)
      module->frames++;

   module->frame_header = 0;

   module->status =
      SEEK(ctx, module->data_offset + module->frames *
         (module->block_size + module->frame_header_size));

   return module->status;
}