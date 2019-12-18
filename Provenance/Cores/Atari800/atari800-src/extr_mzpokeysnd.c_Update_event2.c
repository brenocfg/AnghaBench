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
struct TYPE_3__ {int /*<<< orphan*/  event_2; scalar_t__ c2sw1; scalar_t__ c2sw2; scalar_t__ c2sw3; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 int /*<<< orphan*/  event2_p4 ; 
 int /*<<< orphan*/  event2_p4_p5 ; 
 int /*<<< orphan*/  event2_p5 ; 
 int /*<<< orphan*/  event2_p917 ; 
 int /*<<< orphan*/  event2_p917_p5 ; 
 int /*<<< orphan*/  event2_pure ; 

__attribute__((used)) static void Update_event2(PokeyState* ps)
{
    if(ps->c2sw3)
    {
        if(ps->c2sw2)
            ps->event_2 = event2_pure;
        else
        {
            if(ps->c2sw1)
                ps->event_2 = event2_p4;
            else
                ps->event_2 = event2_p917;
        }
    }
    else
    {
        if(ps->c2sw2)
            ps->event_2 = event2_p5;
        else
        {
            if(ps->c2sw1)
                ps->event_2 = event2_p4_p5;
            else
                ps->event_2 = event2_p917_p5;
        }
    }
}