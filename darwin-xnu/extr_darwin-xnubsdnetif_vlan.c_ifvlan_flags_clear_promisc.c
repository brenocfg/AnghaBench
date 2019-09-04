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
typedef  TYPE_1__* ifvlan_ref ;
struct TYPE_3__ {int /*<<< orphan*/  ifv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFVF_PROMISC ; 

__attribute__((used)) static __inline__ void
ifvlan_flags_clear_promisc(ifvlan_ref ifv)
{
    ifv->ifv_flags &= ~IFVF_PROMISC;
    return;
}