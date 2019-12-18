#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioc_s {int /*<<< orphan*/  ad_cap_bm; int /*<<< orphan*/  port_mode_cfg; int /*<<< orphan*/  port_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip_rev; scalar_t__ pcifn; int /*<<< orphan*/  device_id; } ;
struct bfa_ioc_attr_s {int def_fn; TYPE_1__ pci_attr; int /*<<< orphan*/  adapter_attr; int /*<<< orphan*/  ioc_type; int /*<<< orphan*/  cap_bm; int /*<<< orphan*/  port_mode_cfg; int /*<<< orphan*/  port_mode; scalar_t__ port_id; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_devid (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_get_adapter_attr (struct bfa_ioc_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_ioc_get_pci_chip_rev (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_state (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_get_type (struct bfa_ioc_s*) ; 
 scalar_t__ bfa_ioc_pcifn (struct bfa_ioc_s*) ; 
 scalar_t__ bfa_ioc_portid (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void
bfa_ioc_get_attr(struct bfa_ioc_s *ioc, struct bfa_ioc_attr_s *ioc_attr)
{
	memset((void *)ioc_attr, 0, sizeof(struct bfa_ioc_attr_s));

	ioc_attr->state = bfa_ioc_get_state(ioc);
	ioc_attr->port_id = bfa_ioc_portid(ioc);
	ioc_attr->port_mode = ioc->port_mode;
	ioc_attr->port_mode_cfg = ioc->port_mode_cfg;
	ioc_attr->cap_bm = ioc->ad_cap_bm;

	ioc_attr->ioc_type = bfa_ioc_get_type(ioc);

	bfa_ioc_get_adapter_attr(ioc, &ioc_attr->adapter_attr);

	ioc_attr->pci_attr.device_id = bfa_ioc_devid(ioc);
	ioc_attr->pci_attr.pcifn = bfa_ioc_pcifn(ioc);
	ioc_attr->def_fn = (bfa_ioc_pcifn(ioc) == bfa_ioc_portid(ioc));
	bfa_ioc_get_pci_chip_rev(ioc, ioc_attr->pci_attr.chip_rev);
}