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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {int dummy; } ;
struct mce {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC (int) ; 
 scalar_t__ F10_NBSL_EXT_ERR_ECC ; 
 scalar_t__ NBSL_PP_OBS ; 
 scalar_t__ PP (int /*<<< orphan*/ ) ; 
 scalar_t__ XEC (int,int) ; 
 int /*<<< orphan*/  amd64_handle_ce (struct mem_ctl_info*,struct mce*) ; 
 int /*<<< orphan*/  amd64_handle_ue (struct mem_ctl_info*,struct mce*) ; 

__attribute__((used)) static inline void __amd64_decode_bus_error(struct mem_ctl_info *mci,
					    struct mce *m)
{
	u16 ec = EC(m->status);
	u8 xec = XEC(m->status, 0x1f);
	u8 ecc_type = (m->status >> 45) & 0x3;

	/* Bail early out if this was an 'observed' error */
	if (PP(ec) == NBSL_PP_OBS)
		return;

	/* Do only ECC errors */
	if (xec && xec != F10_NBSL_EXT_ERR_ECC)
		return;

	if (ecc_type == 2)
		amd64_handle_ce(mci, m);
	else if (ecc_type == 1)
		amd64_handle_ue(mci, m);
}