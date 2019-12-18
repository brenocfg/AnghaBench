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
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ arm_apcs_32 ; 
 scalar_t__ arm_pc_is_thumb (int) ; 

__attribute__((used)) static CORE_ADDR
arm_addr_bits_remove (CORE_ADDR val)
{
  if (arm_apcs_32)
    return (val & (arm_pc_is_thumb (val) ? 0xfffffffe : 0xfffffffc));
  else
    return (val & 0x03fffffc);
}