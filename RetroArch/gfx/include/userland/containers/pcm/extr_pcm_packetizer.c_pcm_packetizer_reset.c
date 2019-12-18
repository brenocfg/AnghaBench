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
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ VC_PACKETIZER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_5__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_NEW_PACKET ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T pcm_packetizer_reset( VC_PACKETIZER_T *p_ctx )
{
   VC_PACKETIZER_MODULE_T *module = p_ctx->priv->module;
   module->state = STATE_NEW_PACKET;
   return VC_CONTAINER_SUCCESS;
}