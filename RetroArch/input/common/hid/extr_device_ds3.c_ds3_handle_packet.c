#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_2__* pad; } ;
typedef  TYPE_3__ ds3_instance_t ;
struct TYPE_5__ {TYPE_1__* iface; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* packet_handler ) (void*,int /*<<< orphan*/ *,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void ds3_handle_packet(void *data, uint8_t *packet, size_t size)
{
   ds3_instance_t *instance = (ds3_instance_t *)data;

   if(!instance || !instance->pad)
      return;

   instance->pad->iface->packet_handler(data, packet, size);
}