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
struct escd_info_struc {int dummy; } ;

/* Variables and functions */
 int ESCD_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PNP_DS ; 
 int /*<<< orphan*/  PNP_GET_ESCD_INFO ; 
 int /*<<< orphan*/  PNP_TS1 ; 
 int call_pnp_bios (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct escd_info_struc*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_bios_present () ; 

__attribute__((used)) static int __pnp_bios_escd_info(struct escd_info_struc *data)
{
	u16 status;

	if (!pnp_bios_present())
		return ESCD_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_ESCD_INFO, 0, PNP_TS1, 2, PNP_TS1, 4,
			       PNP_TS1, PNP_DS, data,
			       sizeof(struct escd_info_struc), NULL, 0);
	return status;
}