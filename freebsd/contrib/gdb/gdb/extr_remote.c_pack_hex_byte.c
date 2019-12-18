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

/* Variables and functions */
 void** hexchars ; 

__attribute__((used)) static char *
pack_hex_byte (char *pkt, int byte)
{
  *pkt++ = hexchars[(byte >> 4) & 0xf];
  *pkt++ = hexchars[(byte & 0xf)];
  return pkt;
}