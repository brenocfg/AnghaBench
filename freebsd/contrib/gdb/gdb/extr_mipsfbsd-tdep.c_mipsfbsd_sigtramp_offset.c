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
typedef  int LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ MIPS_FBSD_SIGTRAMP_END ; 
 scalar_t__ MIPS_FBSD_SIGTRAMP_START ; 

__attribute__((used)) static LONGEST
mipsfbsd_sigtramp_offset (CORE_ADDR pc)
{
  return pc < MIPS_FBSD_SIGTRAMP_END && 
         pc >= MIPS_FBSD_SIGTRAMP_START ? 1 : -1;
}