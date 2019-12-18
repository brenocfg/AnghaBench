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
typedef  int /*<<< orphan*/  Job ;
typedef  int /*<<< orphan*/  Conn ;

/* Variables and functions */
 int /*<<< orphan*/  is_job_reserved_by_conn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * remove_this_reserved_job (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Job *
remove_reserved_job(Conn *c, Job *j)
{
    if (!is_job_reserved_by_conn(c, j))
        return NULL;
    return remove_this_reserved_job(c, j);
}