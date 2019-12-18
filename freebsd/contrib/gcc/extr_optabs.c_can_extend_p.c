#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
typedef  TYPE_2__* convert_optab ;
struct TYPE_6__ {TYPE_1__** handlers; } ;
struct TYPE_5__ {int insn_code; } ;

/* Variables and functions */
 int CODE_FOR_ptr_extend ; 
 TYPE_2__* sext_optab ; 
 TYPE_2__* zext_optab ; 

enum insn_code
can_extend_p (enum machine_mode to_mode, enum machine_mode from_mode,
	      int unsignedp)
{
  convert_optab tab;
#ifdef HAVE_ptr_extend
  if (unsignedp < 0)
    return CODE_FOR_ptr_extend;
#endif

  tab = unsignedp ? zext_optab : sext_optab;
  return tab->handlers[to_mode][from_mode].insn_code;
}