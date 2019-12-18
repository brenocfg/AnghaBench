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
typedef  int u8_t ;
typedef  int u32_t ;

/* Variables and functions */
 int lwip_htonl (int) ; 

u8_t
ip4_addr_netmask_valid(u32_t netmask)
{
  u32_t mask;
  u32_t nm_hostorder = lwip_htonl(netmask);

  /* first, check for the first zero */
  for (mask = 1UL << 31 ; mask != 0; mask >>= 1) {
    if ((nm_hostorder & mask) == 0) {
      break;
    }
  }
  /* then check that there is no one */
  for (; mask != 0; mask >>= 1) {
    if ((nm_hostorder & mask) != 0) {
      /* there is a one after the first zero -> invalid */
      return 0;
    }
  }
  /* no one after the first zero -> valid */
  return 1;
}