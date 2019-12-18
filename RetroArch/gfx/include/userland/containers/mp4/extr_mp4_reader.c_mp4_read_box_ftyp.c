#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_10__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {int /*<<< orphan*/  brand; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_9__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_READ_FOURCC (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_FOURCC (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U32 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_2__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_read_box_ftyp( VC_CONTAINER_T *p_ctx, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;

   module->brand = MP4_READ_FOURCC(p_ctx, "major_brand");
   MP4_SKIP_U32(p_ctx, "minor_version");
   while(size >= 4) MP4_SKIP_FOURCC(p_ctx, "compatible_brands");

   return STREAM_STATUS(p_ctx);
}