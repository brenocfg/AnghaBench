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
typedef  int bfd_vma ;
typedef  int bfd_byte ;

/* Variables and functions */
 scalar_t__ ieee_number_repeat_4_enum ; 

__attribute__((used)) static void
ieee_write_int5 (bfd_byte *buffer, bfd_vma value)
{
  buffer[0] = (bfd_byte) ieee_number_repeat_4_enum;
  buffer[1] = (value >> 24) & 0xff;
  buffer[2] = (value >> 16) & 0xff;
  buffer[3] = (value >> 8) & 0xff;
  buffer[4] = (value >> 0) & 0xff;
}