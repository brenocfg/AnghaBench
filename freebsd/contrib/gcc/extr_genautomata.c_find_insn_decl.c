#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decl_t ;
struct TYPE_6__ {char const* name; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 TYPE_3__* DECL_INSN_RESERV (TYPE_1__*) ; 
 int /*<<< orphan*/  dm_insn_reserv ; 
 void* htab_find (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  insn_decl_table ; 
 TYPE_1__ work_insn_decl ; 

__attribute__((used)) static decl_t
find_insn_decl (const char *name)
{
  void *entry;

  work_insn_decl.mode = dm_insn_reserv;
  DECL_INSN_RESERV (&work_insn_decl)->name = name;
  entry = htab_find (insn_decl_table, &work_insn_decl);
  return (decl_t) entry;
}