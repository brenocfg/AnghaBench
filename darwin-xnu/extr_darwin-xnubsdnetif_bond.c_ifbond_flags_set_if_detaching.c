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
typedef  TYPE_1__* ifbond_ref ;
struct TYPE_3__ {int /*<<< orphan*/  ifb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFBF_IF_DETACHING ; 

__attribute__((used)) static __inline__ void
ifbond_flags_set_if_detaching(ifbond_ref ifb)
{
    ifb->ifb_flags |= IFBF_IF_DETACHING;
    return;
}