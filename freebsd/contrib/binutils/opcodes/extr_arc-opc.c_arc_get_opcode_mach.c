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

/* Variables and functions */
#define  ARC_MACH_5 131 
#define  ARC_MACH_6 130 
#define  ARC_MACH_7 129 
#define  ARC_MACH_8 128 
 int ARC_MACH_BIG ; 
 int bfd_mach_arc_5 ; 

int
arc_get_opcode_mach (int bfd_mach, int big_p)
{
  static int mach_type_map[] =
  {
    ARC_MACH_5,
    ARC_MACH_6,
    ARC_MACH_7,
    ARC_MACH_8
  };
  return mach_type_map[bfd_mach - bfd_mach_arc_5] | (big_p ? ARC_MACH_BIG : 0);
}