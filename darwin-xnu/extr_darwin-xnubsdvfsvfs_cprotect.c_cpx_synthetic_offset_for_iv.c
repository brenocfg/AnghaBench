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
 int /*<<< orphan*/  CPX_SYNTHETIC_OFFSET_FOR_IV ; 
 int ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool cpx_synthetic_offset_for_iv(const struct cpx *cpx)
{
	return ISSET(cpx->cpx_flags, CPX_SYNTHETIC_OFFSET_FOR_IV);
}