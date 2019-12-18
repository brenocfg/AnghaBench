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
struct TYPE_4__ {int pri; } ;
struct TYPE_5__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  TUBE_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertf (int,char*) ; 
 int /*<<< orphan*/  default_tube ; 
 TYPE_2__* make_job (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tube (char*) ; 

void
cttest_job_creation()
{
    Job *j;

    TUBE_ASSIGN(default_tube, make_tube("default"));
    j = make_job(1, 0, 1, 0, default_tube);
    assertf(j->r.pri == 1, "priority should match");
}