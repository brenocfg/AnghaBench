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
struct uv_systab {int /*<<< orphan*/  function; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum uv_bios_cmd { ____Placeholder_uv_bios_cmd } uv_bios_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_STATUS_UNIMPLEMENTED ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efi_call6 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uv_systab uv_systab ; 

s64 uv_bios_call(enum uv_bios_cmd which, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5)
{
	struct uv_systab *tab = &uv_systab;
	s64 ret;

	if (!tab->function)
		/*
		 * BIOS does not support UV systab
		 */
		return BIOS_STATUS_UNIMPLEMENTED;

	ret = efi_call6((void *)__va(tab->function), (u64)which,
			a1, a2, a3, a4, a5);
	return ret;
}