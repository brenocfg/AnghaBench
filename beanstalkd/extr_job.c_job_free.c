#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_7__ {TYPE_1__ r; int /*<<< orphan*/  tube; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 scalar_t__ Copy ; 
 int /*<<< orphan*/  TUBE_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  job_hash_free (TYPE_2__*) ; 

void
job_free(Job *j)
{
    if (j) {
        TUBE_ASSIGN(j->tube, NULL);
        if (j->r.state != Copy) job_hash_free(j);
    }

    free(j);
}