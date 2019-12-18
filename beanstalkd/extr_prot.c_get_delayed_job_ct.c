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
typedef  int /*<<< orphan*/  uint ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_5__ {TYPE_1__ delay; } ;
typedef  TYPE_2__ Tube ;
struct TYPE_6__ {size_t len; TYPE_2__** items; } ;

/* Variables and functions */
 TYPE_3__ tubes ; 

__attribute__((used)) static uint
get_delayed_job_ct()
{
    size_t i;
    uint count = 0;

    for (i = 0; i < tubes.len; i++) {
        Tube *t = tubes.items[i];
        count += t->delay.len;
    }
    return count;
}