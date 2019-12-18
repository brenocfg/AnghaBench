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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  UV_BIOS_FREQ_BASE ; 
 int /*<<< orphan*/  uv_bios_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s64 uv_bios_freq_base(u64 clock_type, u64 *ticks_per_second)
{
	return uv_bios_call(UV_BIOS_FREQ_BASE, clock_type,
			   (u64)ticks_per_second, 0, 0, 0);
}