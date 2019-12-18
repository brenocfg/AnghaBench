#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ deadline_at; scalar_t__ id; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */

int
job_delay_less(void *ja, void *jb)
{
    Job *a = ja;
    Job *b = jb;
    if (a->r.deadline_at < b->r.deadline_at) return 1;
    if (a->r.deadline_at > b->r.deadline_at) return 0;
    return a->r.id < b->r.id;
}