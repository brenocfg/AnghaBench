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
struct cpx {scalar_t__ cpx_key_len; } ;

/* Variables and functions */

bool cpx_has_key(const struct cpx *cpx)
{
	return cpx->cpx_key_len > 0;
}