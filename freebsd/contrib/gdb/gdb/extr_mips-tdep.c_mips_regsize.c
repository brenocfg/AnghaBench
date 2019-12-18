#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gdbarch {int dummy; } ;
struct TYPE_2__ {int bits_per_word; int bits_per_byte; } ;

/* Variables and functions */
 TYPE_1__* gdbarch_bfd_arch_info (struct gdbarch*) ; 

int
mips_regsize (struct gdbarch *gdbarch)
{
  return (gdbarch_bfd_arch_info (gdbarch)->bits_per_word
	  / gdbarch_bfd_arch_info (gdbarch)->bits_per_byte);
}