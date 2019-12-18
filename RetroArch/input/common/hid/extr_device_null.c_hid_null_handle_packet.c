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
typedef  TYPE_3__ hid_null_instance_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__* iface; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* packet_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void hid_null_handle_packet(void *data, uint8_t *buffer, size_t size)
{
   hid_null_instance_t *instance = (hid_null_instance_t *)data;

   if (instance && instance->pad)
      instance->pad->iface->packet_handler(instance->pad->data, buffer, size);
}