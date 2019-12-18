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
typedef  void* uint32_t ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
struct TYPE_4__ {void* verbosity; } ;

/* Variables and functions */
 void* verbosity_mask ; 

void vc_container_log_set_verbosity(VC_CONTAINER_T *ctx, uint32_t mask)
{
   if(!ctx) verbosity_mask = mask;
   else ctx->priv->verbosity = mask;
}