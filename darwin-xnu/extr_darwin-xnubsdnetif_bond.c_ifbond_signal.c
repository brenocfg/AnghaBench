#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifbond_ref ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {scalar_t__ verbose; } ;
struct TYPE_5__ {char* ifb_name; } ;

/* Variables and functions */
 TYPE_4__* g_bond ; 
 int /*<<< orphan*/  ifbond_flags_clear_change_in_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ifbond_signal(ifbond_ref ifb, const char * msg)
{
    ifbond_flags_clear_change_in_progress(ifb);
    wakeup((caddr_t)ifb);
    if (g_bond->verbose) {
	printf("%s: %s wakeup\n", ifb->ifb_name, msg);
    }
    return;
}