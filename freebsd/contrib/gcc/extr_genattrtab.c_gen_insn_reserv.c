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
struct insn_reserv {int bypassed; struct insn_reserv* next; int /*<<< orphan*/  insn_num; int /*<<< orphan*/  condexp; int /*<<< orphan*/  default_latency; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_ATTR_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_attr_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct insn_reserv** last_insn_reserv_p ; 
 int /*<<< orphan*/  n_insn_reservs ; 
 struct insn_reserv* oballoc (int) ; 

__attribute__((used)) static void
gen_insn_reserv (rtx def)
{
  struct insn_reserv *decl = oballoc (sizeof (struct insn_reserv));

  decl->name            = DEF_ATTR_STRING (XSTR (def, 0));
  decl->default_latency = XINT (def, 1);
  decl->condexp         = check_attr_test (XEXP (def, 2), 0, 0);
  decl->insn_num        = n_insn_reservs;
  decl->bypassed	= false;
  decl->next            = 0;
  
  *last_insn_reserv_p = decl;
  last_insn_reserv_p  = &decl->next;
  n_insn_reservs++;
}