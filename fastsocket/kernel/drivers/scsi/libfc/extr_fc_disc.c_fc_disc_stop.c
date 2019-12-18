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
struct fc_disc {int /*<<< orphan*/  disc_work; scalar_t__ pending; } ;
struct fc_lport {struct fc_disc disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_disc_stop_rports (struct fc_disc*) ; 

__attribute__((used)) static void fc_disc_stop(struct fc_lport *lport)
{
	struct fc_disc *disc = &lport->disc;

	if (disc->pending)
		cancel_delayed_work_sync(&disc->disc_work);
	fc_disc_stop_rports(disc);
}