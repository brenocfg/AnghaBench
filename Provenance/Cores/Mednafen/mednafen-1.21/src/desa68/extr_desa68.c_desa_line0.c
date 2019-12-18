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
 scalar_t__ check_desa_IMM_SR () ; 
 scalar_t__ check_desa_bitop () ; 
 scalar_t__ check_desa_imm_op () ; 
 scalar_t__ check_desa_movep () ; 
 int /*<<< orphan*/  desa_dcw () ; 

__attribute__((used)) static void desa_line0(void)
{
  if(check_desa_movep() ) 	return;
  if(check_desa_bitop() ) 	return;
  if(check_desa_IMM_SR() ) 	return;
  if(check_desa_imm_op() )	return;
  else desa_dcw();
}