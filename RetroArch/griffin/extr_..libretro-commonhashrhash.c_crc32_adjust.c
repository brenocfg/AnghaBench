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

/* Variables and functions */
 int* crc32_hash_table ; 

uint32_t crc32_adjust(uint32_t checksum, uint8_t input)
{
   return ((checksum >> 8) & 0x00ffffff) ^ crc32_hash_table[(checksum ^ input) & 0xff];
}