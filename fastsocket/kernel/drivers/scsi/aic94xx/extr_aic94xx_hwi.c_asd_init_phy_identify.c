#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int role; int /*<<< orphan*/  id; int /*<<< orphan*/  tproto; int /*<<< orphan*/  iproto; } ;
struct asd_phy {TYPE_3__ sas_phy; TYPE_4__* identify_frame; TYPE_2__* phy_desc; TYPE_1__* id_frm_tok; } ;
struct TYPE_8__ {int /*<<< orphan*/  phy_id; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  target_bits; int /*<<< orphan*/  initiator_bits; int /*<<< orphan*/  dev_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  sas_addr; } ;
struct TYPE_5__ {TYPE_4__* vaddr; } ;

/* Variables and functions */
 int PHY_ROLE_INITIATOR ; 
 int PHY_ROLE_TARGET ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  SAS_END_DEV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asd_init_phy_identify(struct asd_phy *phy)
{
	phy->identify_frame = phy->id_frm_tok->vaddr;

	memset(phy->identify_frame, 0, sizeof(*phy->identify_frame));

	phy->identify_frame->dev_type = SAS_END_DEV;
	if (phy->sas_phy.role & PHY_ROLE_INITIATOR)
		phy->identify_frame->initiator_bits = phy->sas_phy.iproto;
	if (phy->sas_phy.role & PHY_ROLE_TARGET)
		phy->identify_frame->target_bits = phy->sas_phy.tproto;
	memcpy(phy->identify_frame->sas_addr, phy->phy_desc->sas_addr,
	       SAS_ADDR_SIZE);
	phy->identify_frame->phy_id = phy->sas_phy.id;
}