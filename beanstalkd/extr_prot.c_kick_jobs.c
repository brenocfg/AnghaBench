#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  Tube ;
typedef  int /*<<< orphan*/  Server ;

/* Variables and functions */
 scalar_t__ buried_job_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kick_buried_jobs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kick_delayed_jobs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint
kick_jobs(Server *s, Tube *t, uint n)
{
    if (buried_job_p(t))
        return kick_buried_jobs(s, t, n);
    return kick_delayed_jobs(s, t, n);
}