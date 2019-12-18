#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_short ;
typedef  int u_char ;
struct TYPE_5__ {int misc2; int misc1; int* timer; } ;
typedef  TYPE_2__ cirrus_state_t ;
struct TYPE_4__ {TYPE_2__ cirrus; } ;
struct TYPE_6__ {TYPE_1__ state; } ;

/* Variables and functions */
 int PD67_MC1_INPACK_ENA ; 
 int PD67_MC1_MEDIA_ENA ; 
 int PD67_MC2_SUSPEND ; 
 scalar_t__ PD67_MISC_CTL_1 ; 
 scalar_t__ PD67_MISC_CTL_2 ; 
 scalar_t__ PD67_TIME_SETUP (int /*<<< orphan*/ ) ; 
 int i365_get (size_t,scalar_t__) ; 
 int /*<<< orphan*/  i365_set (size_t,scalar_t__,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_3__* socket ; 

__attribute__((used)) static void cirrus_set_state(u_short s)
{
    int i;
    u_char misc;
    cirrus_state_t *p = &socket[s].state.cirrus;

    misc = i365_get(s, PD67_MISC_CTL_2);
    i365_set(s, PD67_MISC_CTL_2, p->misc2);
    if (misc & PD67_MC2_SUSPEND) mdelay(50);
    misc = i365_get(s, PD67_MISC_CTL_1);
    misc &= ~(PD67_MC1_MEDIA_ENA | PD67_MC1_INPACK_ENA);
    i365_set(s, PD67_MISC_CTL_1, misc | p->misc1);
    for (i = 0; i < 6; i++)
	i365_set(s, PD67_TIME_SETUP(0)+i, p->timer[i]);
}