#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct decl {int dummy; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  insn_num; int /*<<< orphan*/ * regexp; } ;
struct TYPE_7__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {size_t decls_num; int /*<<< orphan*/  insns_num; TYPE_2__** decls; } ;

/* Variables and functions */
 TYPE_4__* DECL_INSN_RESERV (TYPE_2__*) ; 
 TYPE_2__* advance_cycle_insn_decl ; 
 TYPE_2__* create_node (int) ; 
 TYPE_1__* description ; 
 int /*<<< orphan*/  dm_insn_reserv ; 
 int /*<<< orphan*/  no_pos ; 

__attribute__((used)) static void
add_advance_cycle_insn_decl (void)
{
  advance_cycle_insn_decl = create_node (sizeof (struct decl));
  advance_cycle_insn_decl->mode = dm_insn_reserv;
  advance_cycle_insn_decl->pos = no_pos;
  DECL_INSN_RESERV (advance_cycle_insn_decl)->regexp = NULL;
  DECL_INSN_RESERV (advance_cycle_insn_decl)->name = "$advance_cycle";
  DECL_INSN_RESERV (advance_cycle_insn_decl)->insn_num
    = description->insns_num;
  description->decls [description->decls_num] = advance_cycle_insn_decl;
  description->decls_num++;
  description->insns_num++;
}