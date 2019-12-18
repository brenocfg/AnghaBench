#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* oc; } ;
struct TYPE_4__ {scalar_t__ status; } ;
typedef  TYPE_2__ AACContext ;

/* Variables and functions */
 scalar_t__ OC_LOCKED ; 
 scalar_t__ OC_NONE ; 

__attribute__((used)) static int push_output_configuration(AACContext *ac) {
    int pushed = 0;

    if (ac->oc[1].status == OC_LOCKED || ac->oc[0].status == OC_NONE) {
        ac->oc[0] = ac->oc[1];
        pushed = 1;
    }
    ac->oc[1].status = OC_NONE;
    return pushed;
}