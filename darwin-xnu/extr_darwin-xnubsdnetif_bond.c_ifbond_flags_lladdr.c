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
struct TYPE_3__ {int ifb_flags; } ;

/* Variables and functions */
 int IFBF_LLADDR ; 

__attribute__((used)) static __inline__ int
ifbond_flags_lladdr(ifbond_ref ifb)
{
    return ((ifb->ifb_flags & IFBF_LLADDR) != 0);
}