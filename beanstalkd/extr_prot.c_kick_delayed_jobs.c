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
typedef  scalar_t__ uint ;
struct TYPE_4__ {scalar_t__ len; scalar_t__* data; } ;
struct TYPE_5__ {TYPE_1__ delay; } ;
typedef  TYPE_2__ Tube ;
typedef  int /*<<< orphan*/  Server ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  kick_delayed_job (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint
kick_delayed_jobs(Server *s, Tube *t, uint n)
{
    uint i;
    for (i = 0; (i < n) && (t->delay.len > 0); ++i) {
        kick_delayed_job(s, (Job *)t->delay.data[0]);
    }
    return i;
}