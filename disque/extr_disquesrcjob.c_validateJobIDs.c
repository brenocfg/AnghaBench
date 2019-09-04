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
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 scalar_t__ validateJobIdOrReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int validateJobIDs(client *c, robj **ids, int count) {
    int j;

    /* Mass-validate the Job IDs, so if we have to stop with an error, nothing
     * at all is processed. */
    for (j = 0; j < count; j++) {
        if (validateJobIdOrReply(c,ids[j]->ptr,sdslen(ids[j]->ptr))
            == C_ERR) return C_ERR;
    }
    return C_OK;
}