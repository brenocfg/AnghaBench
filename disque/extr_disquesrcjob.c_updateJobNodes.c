#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  nodes_delivered; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ job ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ clusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupJob (int /*<<< orphan*/ ) ; 

void updateJobNodes(job *j) {
    job *old = lookupJob(j->id);
    if (!old) return;

    dictIterator *di = dictGetIterator(j->nodes_delivered);
    dictEntry *de;

    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);
        dictAdd(old->nodes_delivered,node->name,node);
    }
    dictReleaseIterator(di);
}