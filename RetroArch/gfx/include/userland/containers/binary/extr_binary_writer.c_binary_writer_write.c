#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ VC_CONTAINER_PACKET_T ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T binary_writer_write( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *packet )
{
   WRITE_BYTES(p_ctx, packet->data, packet->size);
   return STREAM_STATUS(p_ctx);
}