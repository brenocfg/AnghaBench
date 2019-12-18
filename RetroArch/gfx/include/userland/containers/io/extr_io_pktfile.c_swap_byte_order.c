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

__attribute__((used)) static uint32_t swap_byte_order( uint32_t value )
{
   /* Reverse the order of the bytes in the word */
   return ((value << 24) | ((value & 0xFF00) << 8) | ((value >> 8) & 0xFF00) | (value >> 24));
}