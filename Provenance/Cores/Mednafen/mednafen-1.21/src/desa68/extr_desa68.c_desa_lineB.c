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
 scalar_t__ check_desa_cmpa () ; 
 scalar_t__ check_desa_cmpm () ; 
 scalar_t__ check_desa_eor_cmp () ; 
 int /*<<< orphan*/  desa_dcw () ; 

__attribute__((used)) static void desa_lineB(void)
{
  if(check_desa_cmpa())		return;
  else if(check_desa_eor_cmp())	return;
  else if(check_desa_cmpm())		return;
  else desa_dcw();
  return;
}