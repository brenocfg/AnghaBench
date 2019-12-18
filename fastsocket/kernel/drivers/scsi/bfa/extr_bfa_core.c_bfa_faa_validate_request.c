#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* attr; } ;
struct bfa_s {TYPE_2__ ioc; } ;
typedef  enum bfa_ioc_type_e { ____Placeholder_bfa_ioc_type_e } bfa_ioc_type_e ;
typedef  int /*<<< orphan*/  bfa_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  card_type; } ;

/* Variables and functions */
 int BFA_IOC_TYPE_FC ; 
 int /*<<< orphan*/  BFA_STATUS_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  BFA_STATUS_IOC_NON_OP ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int bfa_get_type (struct bfa_s*) ; 
 scalar_t__ bfa_ioc_is_operational (TYPE_2__*) ; 
 scalar_t__ bfa_mfg_is_mezz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_status_t
bfa_faa_validate_request(struct bfa_s *bfa)
{
	enum bfa_ioc_type_e	ioc_type = bfa_get_type(bfa);
	u32	card_type = bfa->ioc.attr->card_type;

	if (bfa_ioc_is_operational(&bfa->ioc)) {
		if ((ioc_type != BFA_IOC_TYPE_FC) || bfa_mfg_is_mezz(card_type))
			return BFA_STATUS_FEATURE_NOT_SUPPORTED;
	} else {
		return BFA_STATUS_IOC_NON_OP;
	}

	return BFA_STATUS_OK;
}