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
struct TYPE_2__ {int start; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  coap_log (int /*<<< orphan*/ ,char*,int) ; 
 int num_packet_loss_intervals ; 
 TYPE_1__* packet_loss_intervals ; 
 int packet_loss_level ; 
 scalar_t__ send_packet_count ; 
 scalar_t__ strtol (char const*,char**,int) ; 

int coap_debug_set_packet_loss(const char *loss_level) {
  const char *p = loss_level;
  char *end = NULL;
  int n = (int)strtol(p, &end, 10), i = 0;
  if (end == p || n < 0)
    return 0;
  if (*end == '%') {
    if (n > 100)
      n = 100;
    packet_loss_level = n * 65536 / 100;
    coap_log(LOG_DEBUG, "packet loss level set to %d%%\n", n);
  } else {
    if (n <= 0)
      return 0;
    while (i < 10) {
      packet_loss_intervals[i].start = n;
      if (*end == '-') {
        p = end + 1;
        n = (int)strtol(p, &end, 10);
        if (end == p || n <= 0)
          return 0;
      }
      packet_loss_intervals[i++].end = n;
      if (*end == 0)
        break;
      if (*end != ',')
        return 0;
      p = end + 1;
      n = (int)strtol(p, &end, 10);
      if (end == p || n <= 0)
        return 0;
    }
    if (i == 10)
      return 0;
    num_packet_loss_intervals = i;
  }
  send_packet_count = 0;
  return 1;
}