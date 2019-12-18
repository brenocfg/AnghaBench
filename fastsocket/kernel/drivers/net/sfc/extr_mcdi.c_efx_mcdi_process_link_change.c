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
typedef  size_t u32 ;
struct efx_nic {int /*<<< orphan*/  link_state; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 size_t EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_EVENT_LINKCHANGE_FCNTL ; 
 int /*<<< orphan*/  MCDI_EVENT_LINKCHANGE_LINK_FLAGS ; 
 int /*<<< orphan*/  MCDI_EVENT_LINKCHANGE_LP_CAP ; 
 int /*<<< orphan*/  MCDI_EVENT_LINKCHANGE_SPEED ; 
 int /*<<< orphan*/  efx_link_status_changed (struct efx_nic*) ; 
 size_t* efx_mcdi_event_link_speed ; 
 int /*<<< orphan*/  efx_mcdi_phy_check_fcntl (struct efx_nic*,size_t) ; 
 int /*<<< orphan*/  efx_mcdi_phy_decode_link (struct efx_nic*,int /*<<< orphan*/ *,size_t,size_t,size_t) ; 

__attribute__((used)) static void efx_mcdi_process_link_change(struct efx_nic *efx, efx_qword_t *ev)
{
	u32 flags, fcntl, speed, lpa;

	speed = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_SPEED);
	EFX_BUG_ON_PARANOID(speed >= ARRAY_SIZE(efx_mcdi_event_link_speed));
	speed = efx_mcdi_event_link_speed[speed];

	flags = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_LINK_FLAGS);
	fcntl = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_FCNTL);
	lpa = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_LP_CAP);

	/* efx->link_state is only modified by efx_mcdi_phy_get_link(),
	 * which is only run after flushing the event queues. Therefore, it
	 * is safe to modify the link state outside of the mac_lock here.
	 */
	efx_mcdi_phy_decode_link(efx, &efx->link_state, speed, flags, fcntl);

	efx_mcdi_phy_check_fcntl(efx, lpa);

	efx_link_status_changed(efx);
}