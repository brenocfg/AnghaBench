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
 int const HAS_MARKER ; 

__attribute__((used)) static bool marker_bit_set(const uint8_t *buffer, size_t buffer_len)
{
   if (buffer_len < 2)
      return false;

   return (buffer[1] & HAS_MARKER);
}