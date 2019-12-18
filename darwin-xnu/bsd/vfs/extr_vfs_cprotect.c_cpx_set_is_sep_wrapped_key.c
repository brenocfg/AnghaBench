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
struct cpx {int /*<<< orphan*/  cpx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPX_SEP_WRAPPEDKEY ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cpx_set_is_sep_wrapped_key(struct cpx *cpx, bool v)
{
	if (v)
	SET(cpx->cpx_flags, CPX_SEP_WRAPPEDKEY);
	else
	CLR(cpx->cpx_flags, CPX_SEP_WRAPPEDKEY);
}