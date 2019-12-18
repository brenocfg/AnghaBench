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
struct insn_reserv_decl {int dummy; } ;
struct bypass_decl {struct insn_reserv_decl* in_insn_reserv; struct bypass_decl* next; } ;

/* Variables and functions */

__attribute__((used)) static struct bypass_decl *
find_bypass (struct bypass_decl *bypass_list,
	     struct insn_reserv_decl *in_insn_reserv)
{
  struct bypass_decl *bypass;

  for (bypass = bypass_list; bypass != NULL; bypass = bypass->next)
    if (bypass->in_insn_reserv == in_insn_reserv)
      break;
  return bypass;
}