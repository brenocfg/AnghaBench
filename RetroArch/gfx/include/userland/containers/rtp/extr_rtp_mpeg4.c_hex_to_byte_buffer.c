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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int hex_to_nybble (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hex_to_byte_buffer(const char *hex,
      uint8_t *buffer,
      uint32_t bytes_to_convert)
{
   uint8_t value;

   while (bytes_to_convert--)
   {
      value = hex_to_nybble(*hex++) << 4;
      value |= hex_to_nybble(*hex++);
      *buffer++ = value;
   }
}