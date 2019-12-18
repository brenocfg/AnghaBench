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
struct bfa_sm_table_s {scalar_t__ sm; int state; } ;
typedef  scalar_t__ bfa_sm_t ;

/* Variables and functions */

__attribute__((used)) static inline int
bfa_sm_to_state(struct bfa_sm_table_s *smt, bfa_sm_t sm)
{
	int	i = 0;

	while (smt[i].sm && smt[i].sm != sm)
		i++;
	return smt[i].state;
}