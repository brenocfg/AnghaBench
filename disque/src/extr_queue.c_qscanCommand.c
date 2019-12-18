#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct qscanFilter {int member_0; int member_1; int member_2; long minlen; long maxlen; long importrate; } ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_13__ {int argc; TYPE_6__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_16__ {char* ptr; } ;
struct TYPE_15__ {int /*<<< orphan*/  queues; } ;
struct TYPE_14__ {int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 long QSCAN_DEFAULT_COUNT ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  addReplyMultiBulkLen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 unsigned long dictScan (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_1__*,TYPE_6__*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listCreate () ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listFirst (int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ parseScanCursorOrReply (TYPE_1__*,TYPE_6__*,unsigned long*) ; 
 int /*<<< orphan*/  qscanCallback ; 
 TYPE_3__ server ; 
 TYPE_2__ shared ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

void qscanCommand(client *c) {
    struct qscanFilter filter = {-1,-1,-1};
    int busyloop = 0; /* If true return all the queues in a blocking way. */
    long count = QSCAN_DEFAULT_COUNT;
    long maxiterations;
    unsigned long cursor = 0;
    int cursor_set = 0, j;

    /* Parse arguments and cursor if any. */
    for (j = 1; j < c->argc; j++) {
        int remaining = c->argc - j -1;
        char *opt = c->argv[j]->ptr;

        if (!strcasecmp(opt,"count") && remaining) {
            if (getLongFromObjectOrReply(c, c->argv[j+1], &count, NULL) !=
                C_OK) return;
            j++;
        } else if (!strcasecmp(opt,"busyloop")) {
            busyloop = 1;
        } else if (!strcasecmp(opt,"minlen") && remaining) {
            if (getLongFromObjectOrReply(c, c->argv[j+1],&filter.minlen,NULL) !=
                C_OK) return;
            j++;
        } else if (!strcasecmp(opt,"maxlen") && remaining) {
            if (getLongFromObjectOrReply(c, c->argv[j+1],&filter.maxlen,NULL) !=
                C_OK) return;
            j++;
        } else if (!strcasecmp(opt,"importrate") && remaining) {
            if (getLongFromObjectOrReply(c, c->argv[j+1],
                &filter.importrate,NULL) != C_OK) return;
            j++;
        } else {
            if (cursor_set != 0) {
                addReply(c,shared.syntaxerr);
                return;
            }
            if (parseScanCursorOrReply(c,c->argv[j],&cursor) == C_ERR)
                return;
            cursor_set = 1;
        }
    }

    /* Scan the hash table to retrieve elements. */
    maxiterations = count*10; /* Put a bound in the work we'll do. */

    /* We pass two pointsr to the callback: the list where to append
     * elements and the filter structure so that the callback will refuse
     * to add non matching elements. */
    void *privdata[2];
    list *list = listCreate();
    privdata[0] = list;
    privdata[1] = &filter;
    do {
        cursor = dictScan(server.queues,cursor,qscanCallback,privdata);
    } while (cursor &&
             (busyloop || /* If it's a busyloop, don't check iterations & len */
              (maxiterations-- &&
               listLength(list) < (unsigned long)count)));

    /* Provide the reply to the client. */
    addReplyMultiBulkLen(c, 2);
    addReplyBulkLongLong(c,cursor);

    addReplyMultiBulkLen(c, listLength(list));
    listNode *node;
    while ((node = listFirst(list)) != NULL) {
        robj *kobj = listNodeValue(node);
        addReplyBulk(c, kobj);
        decrRefCount(kobj);
        listDelNode(list, node);
    }
    listRelease(list);
}