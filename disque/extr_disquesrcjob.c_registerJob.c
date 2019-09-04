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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ job ;
struct TYPE_6__ {int /*<<< orphan*/  jobs; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int DICT_ERR ; 
 int dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  updateJobAwakeTime (TYPE_1__*,int /*<<< orphan*/ ) ; 

int registerJob(job *j) {
    int retval = dictAdd(server.jobs, j->id, NULL);
    if (retval == DICT_ERR) return C_ERR;

    updateJobAwakeTime(j,0);
    return C_OK;
}