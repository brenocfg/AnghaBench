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
 int /*<<< orphan*/  UV_BIOS_GET_PARTITION_ADDR ; 
 int /*<<< orphan*/  uv_bios_call_irqsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s64
uv_bios_reserved_page_pa(u64 buf, u64 *cookie, u64 *addr, u64 *len)
{
	s64 ret;

	ret = uv_bios_call_irqsave(UV_BIOS_GET_PARTITION_ADDR, (u64)cookie,
					(u64)addr, buf, (u64)len, 0);
	return ret;
}