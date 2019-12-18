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
typedef  enum uv_memprotect { ____Placeholder_uv_memprotect } uv_memprotect ;

/* Variables and functions */
 int /*<<< orphan*/  UV_BIOS_MEMPROTECT ; 
 int /*<<< orphan*/  uv_bios_call_irqsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s64
uv_bios_change_memprotect(u64 paddr, u64 len, enum uv_memprotect perms)
{
	return uv_bios_call_irqsave(UV_BIOS_MEMPROTECT, paddr, len,
					perms, 0, 0);
}