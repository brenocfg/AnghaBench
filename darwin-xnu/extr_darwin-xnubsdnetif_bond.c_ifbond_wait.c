#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifbond_ref ;
struct TYPE_8__ {scalar_t__ verbose; } ;
struct TYPE_7__ {char* ifb_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  bond_lck_mtx ; 
 TYPE_6__* g_bond ; 
 scalar_t__ ifbond_flags_change_in_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  ifbond_flags_set_change_in_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  msleep (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 

__attribute__((used)) static void
ifbond_wait(ifbond_ref ifb, const char * msg)
{
    int		waited = 0;

    /* other add/remove in progress */
    while (ifbond_flags_change_in_progress(ifb)) {
	if (g_bond->verbose) {
	    printf("%s: %s msleep\n", ifb->ifb_name, msg);
	}
	waited = 1;
	(void)msleep(ifb, bond_lck_mtx, PZERO, msg, 0);
    }
    /* prevent other bond list remove/add from taking place */
    ifbond_flags_set_change_in_progress(ifb);
    if (g_bond->verbose && waited) {
	printf("%s: %s woke up\n", ifb->ifb_name, msg);
    }
    return;
}