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
typedef  int png_uint_32 ;
typedef  int* png_bytep ;

/* Variables and functions */

__attribute__((used)) static png_uint_32
get32(png_bytep buffer, int offset)
   /* Read a 32-bit value from an 8-byte circular buffer (used only below).
    */
{
   return
      (buffer[ offset    & 7] << 24) +
      (buffer[(offset+1) & 7] << 16) +
      (buffer[(offset+2) & 7] <<  8) +
      (buffer[(offset+3) & 7]      );
}