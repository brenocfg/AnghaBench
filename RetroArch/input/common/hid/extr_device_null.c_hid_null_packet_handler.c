#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  hid_null_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG_BUFFER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hid_null_packet_handler(void *data, uint8_t *packet, uint16_t size)
{
   hid_null_instance_t *instance = (hid_null_instance_t *)data;
   if (!instance)
      return;

   RARCH_LOG_BUFFER(packet, size);
}