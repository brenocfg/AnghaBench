#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 scalar_t__ CODE_FOR_nothing ; 
 TYPE_2__** code_to_optab ; 

int
have_insn_for (enum rtx_code code, enum machine_mode mode)
{
  return (code_to_optab[(int) code] != 0
	  && (code_to_optab[(int) code]->handlers[(int) mode].insn_code
	      != CODE_FOR_nothing));
}