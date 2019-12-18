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
typedef  int uint64_t ;
struct ups_data {int dummy; } ;

/* Variables and functions */
 int ups_patch_read (struct ups_data*) ; 

__attribute__((used)) static uint64_t ups_decode(struct ups_data *data)
{
   uint64_t offset = 0, shift = 1;
   while (true)
   {
      uint8_t x = ups_patch_read(data);
      offset   += (x & 0x7f) * shift;

      if (x & 0x80)
         break;
      shift <<= 7;
      offset += shift;
   }
   return offset;
}