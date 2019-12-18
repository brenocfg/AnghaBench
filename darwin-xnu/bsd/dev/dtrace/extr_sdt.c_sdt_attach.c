#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * sdtp_name; int /*<<< orphan*/  sdtp_id; int /*<<< orphan*/  sdtp_attr; } ;
typedef  TYPE_1__ sdt_provider_t ;
typedef  int /*<<< orphan*/  sdt_probe_t ;
typedef  int /*<<< orphan*/  dev_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_NOTE ; 
 int /*<<< orphan*/  CE_WARN ; 
 scalar_t__ DDI_FAILURE ; 
 int /*<<< orphan*/  DDI_PSEUDO ; 
 int DDI_SUCCESS ; 
 int /*<<< orphan*/  DTRACE_PRIV_KERNEL ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SDT_PROBETAB_SIZE ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ddi_create_minor_node (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_remove_minor_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_invop_add (int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdt_invop ; 
 int /*<<< orphan*/  sdt_pops ; 
 int /*<<< orphan*/  sdt_probetab ; 
 int sdt_probetab_mask ; 
 int sdt_probetab_size ; 
 TYPE_1__* sdt_providers ; 

__attribute__((used)) static int
sdt_attach(dev_info_t *devi)
{
	sdt_provider_t *prov;

	if (ddi_create_minor_node(devi, "sdt", S_IFCHR,
	    0, DDI_PSEUDO, 0) == DDI_FAILURE) {
		cmn_err(CE_NOTE, "/dev/sdt couldn't create minor node");
		ddi_remove_minor_node(devi, NULL);
		return (DDI_FAILURE);
	}

	if (sdt_probetab_size == 0)
		sdt_probetab_size = SDT_PROBETAB_SIZE;

	sdt_probetab_mask = sdt_probetab_size - 1;
	sdt_probetab =
	    kmem_zalloc(sdt_probetab_size * sizeof (sdt_probe_t *), KM_SLEEP);
	dtrace_invop_add(sdt_invop);

	for (prov = sdt_providers; prov->sdtp_name != NULL; prov++) {
		if (dtrace_register(prov->sdtp_name, prov->sdtp_attr,
		    DTRACE_PRIV_KERNEL, NULL,
		    &sdt_pops, prov, &prov->sdtp_id) != 0) {
			cmn_err(CE_WARN, "failed to register sdt provider %s",
			    prov->sdtp_name);
		}
	}

	return (DDI_SUCCESS);
}