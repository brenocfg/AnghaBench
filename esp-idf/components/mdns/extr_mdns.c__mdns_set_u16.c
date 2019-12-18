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
typedef  int uint16_t ;

/* Variables and functions */
 int MDNS_MAX_PACKET_SIZE ; 

__attribute__((used)) static inline void _mdns_set_u16(uint8_t * packet, uint16_t index, uint16_t value)
{
    if ((index + 1) >= MDNS_MAX_PACKET_SIZE) {
        return;
    }
    packet[index] = (value >> 8) & 0xFF;
    packet[index+1] = value & 0xFF;
}