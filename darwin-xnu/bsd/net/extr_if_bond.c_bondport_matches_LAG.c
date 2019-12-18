#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* partner_state_ref ;
typedef  TYPE_2__* bondport_ref ;
struct TYPE_10__ {scalar_t__ li_system_priority; scalar_t__ li_key; int /*<<< orphan*/  li_system; } ;
struct TYPE_9__ {TYPE_4__ lag_info; } ;
struct TYPE_7__ {TYPE_4__ ps_lag_info; } ;
struct TYPE_8__ {TYPE_1__ po_partner_state; } ;
typedef  TYPE_3__* LAG_ref ;
typedef  TYPE_4__* LAG_info_ref ;

/* Variables and functions */
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
bondport_matches_LAG(bondport_ref p, LAG_ref lag)
{
    LAG_info_ref	lag_li;
    partner_state_ref	ps;
    LAG_info_ref	ps_li;

    ps = &p->po_partner_state;
    ps_li = &ps->ps_lag_info;
    lag_li = &lag->lag_info;
    if (ps_li->li_system_priority == lag_li->li_system_priority
	&& ps_li->li_key == lag_li->li_key
	&& (bcmp(&ps_li->li_system, &lag_li->li_system, 
		 sizeof(lag_li->li_system))
	    == 0)) {
	return (1);
    }
    return (0);
}