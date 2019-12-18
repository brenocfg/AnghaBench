#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int num_packet_loss_intervals ; 
 TYPE_1__* packet_loss_intervals ; 
 scalar_t__ packet_loss_level ; 
 int /*<<< orphan*/  prng (int /*<<< orphan*/ *,int) ; 
 scalar_t__ send_packet_count ; 

int coap_debug_send_packet(void) {
  ++send_packet_count;
  if (num_packet_loss_intervals > 0) {
    int i;
    for (i = 0; i < num_packet_loss_intervals; i++) {
      if (send_packet_count >= packet_loss_intervals[i].start
        && send_packet_count <= packet_loss_intervals[i].end)
        return 0;
    }
  }
  if ( packet_loss_level > 0 ) {
    uint16_t r = 0;
    prng( (uint8_t*)&r, 2 );
    if ( r < packet_loss_level )
      return 0;
  }
  return 1;
}