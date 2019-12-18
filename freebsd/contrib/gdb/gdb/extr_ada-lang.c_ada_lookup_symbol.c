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
struct symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  domain_enum ;

/* Variables and functions */
 int ada_lookup_symbol_list (char const*,struct block*,int /*<<< orphan*/ ,struct symbol***,struct block***) ; 
 int /*<<< orphan*/  user_select_syms (struct symbol**,struct block**,int,int) ; 

struct symbol *
ada_lookup_symbol (const char *name, struct block *block0,
		   domain_enum domain)
{
  struct symbol **candidate_syms;
  struct block **candidate_blocks;
  int n_candidates;

  n_candidates = ada_lookup_symbol_list (name,
					 block0, domain,
					 &candidate_syms, &candidate_blocks);

  if (n_candidates == 0)
    return NULL;
  else if (n_candidates != 1)
    user_select_syms (candidate_syms, candidate_blocks, n_candidates, 1);

  return candidate_syms[0];
}