#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  job ;
struct TYPE_9__ {int argc; TYPE_4__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_11__ {TYPE_1__* cluster; } ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_NOFLAGS ; 
 int /*<<< orphan*/  CLUSTERMSG_TYPE_DELJOB ; 
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  clusterBroadcastDelJob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterBroadcastJobIDMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeJob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupJob (int /*<<< orphan*/ ) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  unregisterJob (int /*<<< orphan*/ *) ; 
 scalar_t__ validateJobIDs (TYPE_2__*,TYPE_4__**,int) ; 

void fastackCommand(client *c) {
    int j, known = 0;

    if (validateJobIDs(c,c->argv+1,c->argc-1) == C_ERR) return;

    /* Perform the appropriate action for each job. */
    for (j = 1; j < c->argc; j++) {
        job *job = lookupJob(c->argv[j]->ptr);
        if (job == NULL) {
            /* Job not known, just broadcast the DELJOB message to everybody. */
            clusterBroadcastJobIDMessage(server.cluster->nodes,c->argv[j]->ptr,
                                         CLUSTERMSG_TYPE_DELJOB,0,
                                         CLUSTERMSG_NOFLAGS);
        } else {
            clusterBroadcastDelJob(job);
            unregisterJob(job);
            freeJob(job);
            known++;
        }
    }
    addReplyLongLong(c,known);
}