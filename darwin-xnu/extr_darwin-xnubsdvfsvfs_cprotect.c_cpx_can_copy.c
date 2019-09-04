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
struct cpx {scalar_t__ cpx_key_len; scalar_t__ cpx_max_key_len; } ;

/* Variables and functions */

bool cpx_can_copy(const struct cpx *src, const struct cpx *dst)
{
	return src->cpx_key_len <= dst->cpx_max_key_len;
}