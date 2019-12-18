#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* sample_table; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_18__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_19__ {size_t current_track; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_16__ {int /*<<< orphan*/  entries; } ;
struct TYPE_15__ {TYPE_2__* priv; } ;
struct TYPE_14__ {TYPE_5__* module; } ;
struct TYPE_13__ {TYPE_7__* module; } ;

/* Variables and functions */
 size_t MP4_SAMPLE_TABLE_CTTS ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_6__*) ; 
 int /*<<< orphan*/  WRITE_U24 (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_ctts( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[module->current_track]->priv->module;

   WRITE_U8(p_ctx,  0, "version");
   WRITE_U24(p_ctx, 0, "flags");
   WRITE_U32(p_ctx, track_module->sample_table[MP4_SAMPLE_TABLE_CTTS].entries, "entry_count");
   return STREAM_STATUS(p_ctx);
}