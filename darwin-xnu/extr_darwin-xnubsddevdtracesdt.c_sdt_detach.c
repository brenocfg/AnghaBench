#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sdtp_id; int /*<<< orphan*/ * sdtp_name; } ;
typedef  TYPE_1__ sdt_provider_t ;
typedef  int /*<<< orphan*/  sdt_probe_t ;
typedef  int /*<<< orphan*/  dev_info_t ;
typedef  int ddi_detach_cmd_t ;

/* Variables and functions */
#define  DDI_DETACH 129 
 int DDI_FAILURE ; 
 int DDI_SUCCESS ; 
#define  DDI_SUSPEND 128 
 scalar_t__ DTRACE_PROVNONE ; 
 int /*<<< orphan*/  dtrace_invop_remove (int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_unregister (scalar_t__) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdt_invop ; 
 int /*<<< orphan*/  sdt_probetab ; 
 int sdt_probetab_size ; 
 TYPE_1__* sdt_providers ; 

__attribute__((used)) static int
sdt_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	sdt_provider_t *prov;

	switch (cmd) {
	case DDI_DETACH:
		break;

	case DDI_SUSPEND:
		return (DDI_SUCCESS);

	default:
		return (DDI_FAILURE);
	}

	for (prov = sdt_providers; prov->sdtp_name != NULL; prov++) {
		if (prov->sdtp_id != DTRACE_PROVNONE) {
			if (dtrace_unregister(prov->sdtp_id) != 0)
				return (DDI_FAILURE);

			prov->sdtp_id = DTRACE_PROVNONE;
		}
	}

	dtrace_invop_remove(sdt_invop);
	kmem_free(sdt_probetab, sdt_probetab_size * sizeof (sdt_probe_t *));

	return (DDI_SUCCESS);
}