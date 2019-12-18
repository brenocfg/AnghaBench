#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_5__ {TYPE_1__* shost; } ;
struct sas_ha_struct {TYPE_2__ core; } ;
struct asd_sas_port {int dummy; } ;
struct asd_sas_phy {int error; scalar_t__ enabled; int /*<<< orphan*/  phy_events_pending; struct asd_sas_port* port; struct sas_ha_struct* ha; } ;
struct asd_sas_event {struct asd_sas_phy* phy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* lldd_control_phy ) (struct asd_sas_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYE_OOB_ERROR ; 
 int /*<<< orphan*/  PHY_FUNC_DISABLE ; 
 int /*<<< orphan*/  PHY_FUNC_HARD_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_deform_port (struct asd_sas_phy*,int) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct asd_sas_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct asd_sas_event* to_asd_sas_event (struct work_struct*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sas_phye_oob_error(struct work_struct *work)
{
	struct asd_sas_event *ev = to_asd_sas_event(work);
	struct asd_sas_phy *phy = ev->phy;
	struct sas_ha_struct *sas_ha = phy->ha;
	struct asd_sas_port *port = phy->port;
	struct sas_internal *i =
		to_sas_internal(sas_ha->core.shost->transportt);

	clear_bit(PHYE_OOB_ERROR, &phy->phy_events_pending);

	sas_deform_port(phy, 1);

	if (!port && phy->enabled && i->dft->lldd_control_phy) {
		phy->error++;
		switch (phy->error) {
		case 1:
		case 2:
			i->dft->lldd_control_phy(phy, PHY_FUNC_HARD_RESET,
						 NULL);
			break;
		case 3:
		default:
			phy->error = 0;
			phy->enabled = 0;
			i->dft->lldd_control_phy(phy, PHY_FUNC_DISABLE, NULL);
			break;
		}
	}
}