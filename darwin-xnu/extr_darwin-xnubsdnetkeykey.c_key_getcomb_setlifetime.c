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
struct sadb_comb {int sadb_comb_soft_allocations; int sadb_comb_hard_allocations; int sadb_comb_hard_addtime; int sadb_comb_soft_addtime; int sadb_comb_soft_usetime; int sadb_comb_hard_usetime; scalar_t__ sadb_comb_hard_bytes; scalar_t__ sadb_comb_soft_bytes; } ;

/* Variables and functions */

__attribute__((used)) static void
key_getcomb_setlifetime(
						struct sadb_comb *comb)
{
	
	comb->sadb_comb_soft_allocations = 1;
	comb->sadb_comb_hard_allocations = 1;
	comb->sadb_comb_soft_bytes = 0;
	comb->sadb_comb_hard_bytes = 0;
	comb->sadb_comb_hard_addtime = 86400;	/* 1 day */
	comb->sadb_comb_soft_addtime = comb->sadb_comb_soft_addtime * 80 / 100;
	comb->sadb_comb_soft_usetime = 28800;	/* 8 hours */
	comb->sadb_comb_hard_usetime = comb->sadb_comb_hard_usetime * 80 / 100;
}