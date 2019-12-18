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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  PNP_DS ; 
 int PNP_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PNP_GET_STATIC_ALLOCED_RES_INFO ; 
 int /*<<< orphan*/  PNP_TS1 ; 
 int call_pnp_bios (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_bios_present () ; 

__attribute__((used)) static int __pnp_bios_get_stat_res(char *info)
{
	u16 status;

	if (!pnp_bios_present())
		return PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_STATIC_ALLOCED_RES_INFO, 0, PNP_TS1,
			       PNP_DS, 0, 0, 0, 0, info, 65536, NULL, 0);
	return status;
}