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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  size_t uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t _mdns_read_u32(const uint8_t * packet, uint16_t index)
{
    return (uint32_t)(packet[index]) << 24 | (uint32_t)(packet[index+1]) << 16 | (uint32_t)(packet[index+2]) << 8 | packet[index+3];
}