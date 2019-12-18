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
struct TYPE_2__ {int /*<<< orphan*/  (* rport_flush_queue ) () ;} ;
struct fc_lport {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_disc_stop (struct fc_lport*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void fc_disc_stop_final(struct fc_lport *lport)
{
	fc_disc_stop(lport);
	lport->tt.rport_flush_queue();
}