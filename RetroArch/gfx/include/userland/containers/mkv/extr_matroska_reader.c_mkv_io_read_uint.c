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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_T ;

/* Variables and functions */
 int vc_container_io_read_uint8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t mkv_io_read_uint(VC_CONTAINER_IO_T *io, int64_t *size)
{
   uint64_t value, mask;

   value = vc_container_io_read_uint8(io); (*size)--;
   if(value == 0xFF) return -1;

   for(mask = 0x80; mask; mask <<= 7)
   {
      if(value & mask) return value & ~mask;
      value = (value << 8) | vc_container_io_read_uint8(io); (*size)--;
   }
   return 0;
}