#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashval_t ;
typedef  TYPE_1__* decl_t ;
struct TYPE_5__ {scalar_t__ name; } ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_2__* DECL_INSN_RESERV (TYPE_1__* const) ; 
 scalar_t__ dm_insn_reserv ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  string_hash (scalar_t__) ; 

__attribute__((used)) static hashval_t
insn_decl_hash (const void *insn_decl)
{
  const decl_t decl = (decl_t) insn_decl;

  gcc_assert (decl->mode == dm_insn_reserv
	      && DECL_INSN_RESERV (decl)->name);
  return string_hash (DECL_INSN_RESERV (decl)->name);
}