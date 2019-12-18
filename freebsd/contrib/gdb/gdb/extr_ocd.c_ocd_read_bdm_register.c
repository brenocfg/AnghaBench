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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  extract_unsigned_integer (unsigned char*,int) ; 
 unsigned char* ocd_read_bdm_registers (int,int,int*) ; 

CORE_ADDR
ocd_read_bdm_register (int bdm_regno)
{
  int reglen;
  unsigned char *p;
  CORE_ADDR regval;

  p = ocd_read_bdm_registers (bdm_regno, bdm_regno, &reglen);
  regval = extract_unsigned_integer (p, reglen);

  return regval;
}