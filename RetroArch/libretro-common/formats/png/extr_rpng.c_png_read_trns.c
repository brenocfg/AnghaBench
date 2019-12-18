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

__attribute__((used)) static bool png_read_trns(uint8_t *buf, uint32_t *palette, unsigned entries)
{
   unsigned i;

   for (i = 0; i < entries; i++, buf++, palette++)
      *palette = (*palette & 0x00ffffff) | (unsigned)*buf << 24;

   return true;
}