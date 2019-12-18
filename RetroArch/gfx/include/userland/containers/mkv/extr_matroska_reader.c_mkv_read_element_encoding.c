#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  encodings_num; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_13__ {TYPE_1__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_14__ {TYPE_3__* parsing; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {TYPE_4__* module; } ;
struct TYPE_9__ {TYPE_6__* module; } ;
typedef  int /*<<< orphan*/  MKV_ELEMENT_ID_T ;

/* Variables and functions */
 int /*<<< orphan*/  mkv_read_elements (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_element_encoding( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = module->parsing->priv->module;
   VC_CONTAINER_STATUS_T status;
   status = mkv_read_elements(p_ctx, id, size);
   track_module->encodings_num++;
   return status;
}