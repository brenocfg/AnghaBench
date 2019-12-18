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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ds3_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  HID_SET_PROTOCOL (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t set_protocol(ds3_instance_t *instance, int protocol)
{
   uint32_t result = 0;
#if defined(WIIU)
   result = HID_SET_PROTOCOL(instance->handle, 1);
#endif

   return result;
}