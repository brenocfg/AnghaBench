#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
struct TYPE_4__ {int /*<<< orphan*/ * module_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  unload_library (int /*<<< orphan*/ *) ; 

void vc_container_unload(VC_CONTAINER_T *p_ctx)
{
   if (p_ctx->priv->module_handle)
   {
      unload_library(p_ctx->priv->module_handle);
      p_ctx->priv->module_handle = NULL;
   }
}