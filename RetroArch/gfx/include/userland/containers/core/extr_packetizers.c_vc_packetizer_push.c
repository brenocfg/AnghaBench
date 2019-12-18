#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_9__ {scalar_t__ framework_data; } ;
typedef  TYPE_3__ VC_CONTAINER_PACKET_T ;
struct TYPE_7__ {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  bytestream_push (int /*<<< orphan*/ *,TYPE_3__*) ; 

VC_CONTAINER_STATUS_T vc_packetizer_push( VC_PACKETIZER_T *p_ctx,
   VC_CONTAINER_PACKET_T *in)
{
   /* Do some sanity checking on packet ? */

   in->framework_data = 0;
   bytestream_push(&p_ctx->priv->stream, in);
   return VC_CONTAINER_SUCCESS;
}