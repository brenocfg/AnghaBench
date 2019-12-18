#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* elos; } ;
typedef  TYPE_1__ sortable_bbox ;

/* Variables and functions */
 int pow (int,int) ; 

void bbox_update(sortable_bbox *a, sortable_bbox *b, int class, int result)
{
    int k = 32;
    float EA = 1./(1+pow(10, (b->elos[class] - a->elos[class])/400.));
    float EB = 1./(1+pow(10, (a->elos[class] - b->elos[class])/400.));
    float SA = result ? 1 : 0;
    float SB = result ? 0 : 1;
    a->elos[class] += k*(SA - EA);
    b->elos[class] += k*(SB - EB);
}