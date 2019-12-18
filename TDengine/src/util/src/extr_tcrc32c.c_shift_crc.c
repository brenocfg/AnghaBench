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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t shift_crc(uint32_t shift_table[][256], uint32_t crc) {
  return shift_table[0][crc & 0xff] ^ shift_table[1][(crc >> 8) & 0xff] ^
         shift_table[2][(crc >> 16) & 0xff] ^ shift_table[3][crc >> 24];
}