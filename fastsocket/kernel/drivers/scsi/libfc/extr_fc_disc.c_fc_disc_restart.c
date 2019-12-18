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
struct fc_disc {int requested; int disc_id; scalar_t__ retry_count; scalar_t__ pending; int /*<<< orphan*/  disc_callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_DISC_DBG (struct fc_disc*,char*) ; 
 int /*<<< orphan*/  fc_disc_gpn_ft_req (struct fc_disc*) ; 

__attribute__((used)) static void fc_disc_restart(struct fc_disc *disc)
{
	if (!disc->disc_callback)
		return;

	FC_DISC_DBG(disc, "Restarting discovery\n");

	disc->requested = 1;
	if (disc->pending)
		return;

	/*
	 * Advance disc_id.  This is an arbitrary non-zero number that will
	 * match the value in the fc_rport_priv after discovery for all
	 * freshly-discovered remote ports.  Avoid wrapping to zero.
	 */
	disc->disc_id = (disc->disc_id + 2) | 1;
	disc->retry_count = 0;
	fc_disc_gpn_ft_req(disc);
}