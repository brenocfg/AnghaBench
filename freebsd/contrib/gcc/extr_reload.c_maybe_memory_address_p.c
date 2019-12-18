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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int memory_address_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
maybe_memory_address_p (enum machine_mode mode, rtx ad, rtx *part)
{
  int retv;
  rtx tem = *part;
  rtx reg = gen_rtx_REG (GET_MODE (tem), max_reg_num ());

  *part = reg;
  retv = memory_address_p (mode, ad);
  *part = tem;

  return retv;
}