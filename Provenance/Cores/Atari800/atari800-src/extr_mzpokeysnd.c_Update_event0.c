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
struct TYPE_3__ {int /*<<< orphan*/  event_0; scalar_t__ c0sw1; scalar_t__ c0sw2; scalar_t__ c0sw3; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 int /*<<< orphan*/  event0_p4 ; 
 int /*<<< orphan*/  event0_p4_p5 ; 
 int /*<<< orphan*/  event0_p5 ; 
 int /*<<< orphan*/  event0_p917 ; 
 int /*<<< orphan*/  event0_p917_p5 ; 
 int /*<<< orphan*/  event0_pure ; 

__attribute__((used)) static void Update_event0(PokeyState* ps)
{
    if(ps->c0sw3)
    {
        if(ps->c0sw2)
            ps->event_0 = event0_pure;
        else
        {
            if(ps->c0sw1)
                ps->event_0 = event0_p4;
            else
                ps->event_0 = event0_p917;
        }
    }
    else
    {
        if(ps->c0sw2)
            ps->event_0 = event0_p5;
        else
        {
            if(ps->c0sw1)
                ps->event_0 = event0_p4_p5;
            else
                ps->event_0 = event0_p917_p5;
        }
    }
}