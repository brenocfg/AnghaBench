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
typedef  int* crc_stream ;

/* Variables and functions */
 int POLY ; 

__attribute__((used)) static uint32_t append_trivial(uint32_t crc, crc_stream input, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    crc = crc ^ input[i];
    for (int j = 0; j < 8; j++)
      crc = (crc >> 1) ^ 0x80000000 ^ ((~crc & 1) * POLY);
  }
  return crc;
}