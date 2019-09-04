#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct jscanFilter {int* state; int /*<<< orphan*/  numstates; TYPE_5__* queue; } ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  job ;
typedef  int /*<<< orphan*/  filter ;
struct TYPE_15__ {int argc; TYPE_5__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_18__ {char* ptr; } ;
struct TYPE_17__ {int /*<<< orphan*/  jobs; } ;
struct TYPE_16__ {int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 long JSCAN_DEFAULT_COUNT ; 
 int JSCAN_REPLY_ALL ; 
 int JSCAN_REPLY_ID ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  addReplyError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  addReplyJobID (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyJobInfo (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyMultiBulkLen (TYPE_1__*,int) ; 
 unsigned long dictScan (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_1__*,TYPE_5__*,long*,int /*<<< orphan*/ *) ; 
 int jobStateFromString (char*) ; 
 int /*<<< orphan*/  jscanCallback ; 
 int /*<<< orphan*/ * listCreate () ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listFirst (int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct jscanFilter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parseScanCursorOrReply (TYPE_1__*,TYPE_5__*,unsigned long*) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_2__ shared ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

void jscanCommand(client *c) {
    struct jscanFilter filter;
    int busyloop = 0; /* If true return all the jobs in a blocking way. */
    long count = JSCAN_DEFAULT_COUNT;
    long maxiterations;
    unsigned long cursor = 0;
    int cursor_set = 0, j;
    int reply_type = JSCAN_REPLY_ID;

    memset(&filter,0,sizeof(filter));

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
        } else if (!strcasecmp(opt,"queue") && remaining) {
            filter.queue = c->argv[j+1];
            j++;
        } else if (!strcasecmp(opt,"state") && remaining) {
            int jobstate = jobStateFromString(c->argv[j+1]->ptr);
            if (jobstate == -1) {
                addReplyError(c,"Invalid job state name");
                return;
            }
            filter.state[jobstate] = 1;
            filter.numstates++;
            j++;
        } else if (!strcasecmp(opt,"reply") && remaining) {
            if (!strcasecmp(c->argv[j+1]->ptr,"id")) {
                reply_type = JSCAN_REPLY_ID;
            } else if (!strcasecmp(c->argv[j+1]->ptr,"all")) {
                reply_type = JSCAN_REPLY_ALL;
            } else {
                addReplyError(c,"Invalid REPLY type, try ID or ALL");
                return;
            }
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
        cursor = dictScan(server.jobs,cursor,jscanCallback,privdata);
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
        job *j = listNodeValue(node);
        if (reply_type == JSCAN_REPLY_ID) addReplyJobID(c,j);
        else if (reply_type == JSCAN_REPLY_ALL) addReplyJobInfo(c,j);
        else serverPanic("Unknown JSCAN reply type");
        listDelNode(list, node);
    }
    listRelease(list);
}