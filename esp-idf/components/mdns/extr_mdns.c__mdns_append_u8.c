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
typedef  size_t uint16_t ;

/* Variables and functions */
 size_t MDNS_MAX_PACKET_SIZE ; 

__attribute__((used)) static inline uint8_t _mdns_append_u8(uint8_t * packet, uint16_t * index, uint8_t value)
{
    if (*index >= MDNS_MAX_PACKET_SIZE) {
        return 0;
    }
    packet[*index] = value;
    *index += 1;
    return 1;
}