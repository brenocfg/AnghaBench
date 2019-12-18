#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; scalar_t__ num_deliv; scalar_t__ num_nacks; scalar_t__ awakeme; int /*<<< orphan*/ * nodes_confirmed; int /*<<< orphan*/  nodes_delivered; int /*<<< orphan*/ * body; scalar_t__ flags; scalar_t__ gc_retry; int /*<<< orphan*/ * queue; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ job ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_ID_LEN ; 
 int /*<<< orphan*/  clusterNodesDictType ; 
 int /*<<< orphan*/  dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generateJobID (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* zmalloc (int) ; 

job *createJob(char *id, int state, int ttl, int retry) {
    job *j = zmalloc(sizeof(job));

    /* Generate a new Job ID if not specified by the caller. */
    if (id == NULL)
        generateJobID(j->id,ttl,retry);
    else
        memcpy(j->id,id,JOB_ID_LEN);

    j->queue = NULL;
    j->state = state;
    j->gc_retry = 0;
    j->flags = 0;
    j->body = NULL;
    j->nodes_delivered = dictCreate(&clusterNodesDictType,NULL);
    j->nodes_confirmed = NULL; /* Only created later on-demand. */
    j->awakeme = 0; /* Not yet registered in awakeme skiplist. */
    /* Number of NACKs and additiona deliveries start at zero and
     * are incremented as QUEUED messages are received or sent. */
    j->num_nacks = 0;
    j->num_deliv = 0;
    return j;
}