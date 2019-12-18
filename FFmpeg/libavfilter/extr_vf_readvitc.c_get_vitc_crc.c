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

/* Variables and functions */

__attribute__((used)) static uint8_t get_vitc_crc( uint8_t *line ) {
    uint8_t crc;

    crc = 0x01 | (line[0] << 2);
    crc ^= (line[0] >> 6) | 0x04 | (line[1] << 4);
    crc ^= (line[1] >> 4) | 0x10 | (line[2] << 6);
    crc ^= (line[2] >> 2) | 0x40;
    crc ^= line[3];
    crc ^= 0x01 | (line[4] << 2);
    crc ^= (line[4] >> 6) | 0x04 | (line[5] << 4);
    crc ^= (line[5] >> 4) | 0x10 | (line[6] << 6);
    crc ^= (line[6] >> 2) | 0x40;
    crc ^= line[7];
    crc ^= 0x01;
    crc = (crc >> 2) | (crc << 6);  // rotate byte right by two bits
    return crc;
}