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
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_5__ {TYPE_1__ r; int /*<<< orphan*/ * reserver; } ;
typedef  TYPE_2__ Job ;
typedef  int /*<<< orphan*/  Conn ;

/* Variables and functions */
 scalar_t__ Reserved ; 

__attribute__((used)) static bool
is_job_reserved_by_conn(Conn *c, Job *j)
{
    return j && j->reserver == c && j->r.state == Reserved;
}