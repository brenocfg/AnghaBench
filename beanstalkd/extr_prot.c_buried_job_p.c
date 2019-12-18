#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buried; } ;
typedef  TYPE_1__ Tube ;

/* Variables and functions */
 int /*<<< orphan*/  job_list_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
buried_job_p(Tube *t)
{
    // this function does not do much. inline?
    return !job_list_is_empty(&t->buried);
}