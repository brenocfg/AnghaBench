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
typedef  unsigned short u16 ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short const RX_CHANNEL_MASK ; 
 int vpi_bits ; 

__attribute__((used)) static inline int channel_to_vpivci (const u16 channel, short * vpi, int * vci) {
  unsigned short vci_bits = 10 - vpi_bits;
  if ((channel & RX_CHANNEL_MASK) == channel) {
    *vci = channel & ((~0)<<vci_bits);
    *vpi = channel >> vci_bits;
    return channel ? 0 : -EINVAL;
  }
  return -EINVAL;
}