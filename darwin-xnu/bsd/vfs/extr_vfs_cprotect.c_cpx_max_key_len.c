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
typedef  int /*<<< orphan*/  uint16_t ;
struct cpx {int /*<<< orphan*/  cpx_max_key_len; } ;

/* Variables and functions */

uint16_t cpx_max_key_len(const struct cpx *cpx)
{
	return cpx->cpx_max_key_len;
}