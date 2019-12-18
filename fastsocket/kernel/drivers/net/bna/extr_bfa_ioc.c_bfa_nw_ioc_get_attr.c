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
struct TYPE_2__ {int /*<<< orphan*/  chip_rev; int /*<<< orphan*/  pcifn; int /*<<< orphan*/  device_id; } ;
struct bfa_ioc_attr {TYPE_1__ pci_attr; int /*<<< orphan*/  def_fn; int /*<<< orphan*/  adapter_attr; int /*<<< orphan*/  ioc_type; int /*<<< orphan*/  cap_bm; int /*<<< orphan*/  port_mode_cfg; int /*<<< orphan*/  port_mode; int /*<<< orphan*/  port_id; int /*<<< orphan*/  state; } ;
struct bfa_ioc {int /*<<< orphan*/  ad_cap_bm; int /*<<< orphan*/  port_mode_cfg; int /*<<< orphan*/  port_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_devid (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_get_adapter_attr (struct bfa_ioc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_ioc_get_pci_chip_rev (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_get_state (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_get_type (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_is_default (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_pcifn (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (struct bfa_ioc*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void
bfa_nw_ioc_get_attr(struct bfa_ioc *ioc, struct bfa_ioc_attr *ioc_attr)
{
	memset((void *)ioc_attr, 0, sizeof(struct bfa_ioc_attr));

	ioc_attr->state = bfa_ioc_get_state(ioc);
	ioc_attr->port_id = bfa_ioc_portid(ioc);
	ioc_attr->port_mode = ioc->port_mode;

	ioc_attr->port_mode_cfg = ioc->port_mode_cfg;
	ioc_attr->cap_bm = ioc->ad_cap_bm;

	ioc_attr->ioc_type = bfa_ioc_get_type(ioc);

	bfa_ioc_get_adapter_attr(ioc, &ioc_attr->adapter_attr);

	ioc_attr->pci_attr.device_id = bfa_ioc_devid(ioc);
	ioc_attr->pci_attr.pcifn = bfa_ioc_pcifn(ioc);
	ioc_attr->def_fn = bfa_ioc_is_default(ioc);
	bfa_ioc_get_pci_chip_rev(ioc, ioc_attr->pci_attr.chip_rev);
}