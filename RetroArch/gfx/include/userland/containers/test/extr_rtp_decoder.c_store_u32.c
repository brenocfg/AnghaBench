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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void store_u32(uint8_t *buffer, uint32_t value)
{
   buffer[0] = (uint8_t)value;
   buffer[1] = (uint8_t)(value >> 8);
   buffer[2] = (uint8_t)(value >> 16);
   buffer[3] = (uint8_t)(value >> 24);
}