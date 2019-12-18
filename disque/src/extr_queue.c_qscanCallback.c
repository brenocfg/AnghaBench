#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qscanFilter {int minlen; int maxlen; int importrate; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 TYPE_1__* dictGetVal (int /*<<< orphan*/  const*) ; 
 int getQueueImportRate (TYPE_1__*) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queueLength (TYPE_1__*) ; 

void qscanCallback(void *privdata, const dictEntry *de) {
    void **pd = (void**)privdata;
    list *list = pd[0];
    struct qscanFilter *filter = pd[1];
    queue *queue = dictGetVal(de);
    long qlen = (filter->minlen != -1 || filter->maxlen != -1) ?
                    (long) queueLength(queue) : 0;

    /* Don't add the item if it does not satisfies our filter. */
    if (filter->minlen != -1 && qlen < filter->minlen) return;
    if (filter->maxlen != -1 && qlen > filter->maxlen) return;
    if (filter->importrate != -1 &&
        getQueueImportRate(queue) < filter->importrate) return;

    /* Otherwise put the queue into the list that will be returned to the
     * client later. */
    incrRefCount(queue->name);
    listAddNodeTail(list,queue->name);
}