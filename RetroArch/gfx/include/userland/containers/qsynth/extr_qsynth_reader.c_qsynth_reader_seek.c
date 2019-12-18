#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ duration; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  scalar_t__ VC_CONTAINER_SEEK_MODE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAGS_T ;
struct TYPE_7__ {int seek; scalar_t__ timestamp; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_5__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ VC_CONTAINER_SEEK_MODE_TIME ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T qsynth_reader_seek( VC_CONTAINER_T *p_ctx,
                                              int64_t *offset,
                                              VC_CONTAINER_SEEK_MODE_T mode,
                                              VC_CONTAINER_SEEK_FLAGS_T flags)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_PARAM_UNUSED(flags);

   if (mode != VC_CONTAINER_SEEK_MODE_TIME)
      return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;

   if(*offset < 0)
      *offset = 0;
   else if(*offset > p_ctx->duration)
      *offset = p_ctx->duration;

   module->timestamp = *offset;
   module->seek = 1;

   return VC_CONTAINER_SUCCESS;
}