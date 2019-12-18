#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
struct TYPE_7__ {TYPE_2__ d_id; int /*<<< orphan*/  vha; int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ fc_port_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * port_state_str ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 

__attribute__((used)) static inline void
qla2x00_set_fcport_state(fc_port_t *fcport, int state)
{
	int old_state;

	old_state = atomic_read(&fcport->state);
	atomic_set(&fcport->state, state);

	/* Don't print state transitions during initial allocation of fcport */
	if (old_state && old_state != state) {
		ql_dbg(ql_dbg_disc, fcport->vha, 0x207d,
		    "FCPort state transitioned from %s to %s - "
		    "portid=%02x%02x%02x.\n",
		    port_state_str[old_state], port_state_str[state],
		    fcport->d_id.b.domain, fcport->d_id.b.area,
		    fcport->d_id.b.al_pa);
	}
}