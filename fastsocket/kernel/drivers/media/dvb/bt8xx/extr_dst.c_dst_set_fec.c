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
struct dst_state {int /*<<< orphan*/  fec; } ;
typedef  int /*<<< orphan*/  fe_code_rate_t ;

/* Variables and functions */

__attribute__((used)) static int dst_set_fec(struct dst_state *state, fe_code_rate_t fec)
{
	state->fec = fec;
	return 0;
}