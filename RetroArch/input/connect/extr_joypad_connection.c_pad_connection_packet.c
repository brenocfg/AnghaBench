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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ data; TYPE_1__* iface; int /*<<< orphan*/  connected; } ;
typedef  TYPE_2__ joypad_connection_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* packet_handler ) (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void pad_connection_packet(joypad_connection_t *joyconn, uint32_t pad,
      uint8_t* data, uint32_t length)
{
   if (!joyconn || !joyconn->connected)
       return;
   if (joyconn->iface && joyconn->data && joyconn->iface->packet_handler)
      joyconn->iface->packet_handler(joyconn->data, data, length);
}