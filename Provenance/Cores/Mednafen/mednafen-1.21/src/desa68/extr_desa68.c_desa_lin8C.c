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
 scalar_t__ check_desa_abcd_sbcd () ; 
 scalar_t__ check_desa_and_or () ; 
 scalar_t__ check_desa_exg () ; 
 scalar_t__ check_desa_mul_div () ; 
 int /*<<< orphan*/  desa_dcw () ; 

__attribute__((used)) static void desa_lin8C(void)
{
  if(check_desa_abcd_sbcd())	return;
  else if(check_desa_mul_div())		return;
  else if(check_desa_exg())			return;
  else if(check_desa_and_or())		return;
  else desa_dcw();
  return;
}