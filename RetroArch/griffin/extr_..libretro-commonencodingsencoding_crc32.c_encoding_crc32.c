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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* crc32_table ; 

uint32_t encoding_crc32(uint32_t crc, const uint8_t *buf, size_t len)
{
   crc = crc ^ 0xffffffff;

   while (len--)
      crc = crc32_table[(crc ^ (*buf++)) & 0xff] ^ (crc >> 8);

   return crc ^ 0xffffffff;
}