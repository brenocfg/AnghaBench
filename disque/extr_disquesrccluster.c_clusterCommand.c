#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_20__ {int flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_21__ {int argc; TYPE_7__** argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_24__ {scalar_t__ ptr; } ;
struct TYPE_23__ {TYPE_1__* cluster; } ;
struct TYPE_22__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_19__ {size_t state; int /*<<< orphan*/  stats_bus_messages_received; int /*<<< orphan*/  stats_bus_messages_sent; int /*<<< orphan*/  size; int /*<<< orphan*/  reachable_nodes_count; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 scalar_t__ CLUSTER_NAMELEN ; 
 int CLUSTER_NODE_LEAVING ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 scalar_t__ C_OK ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  addReplyBulkSds (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_3__*,char*,char*,...) ; 
 int /*<<< orphan*/  addReplySds (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterBlacklistAddNode (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterDelNode (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterDoBeforeSleep (int) ; 
 int /*<<< orphan*/  clusterGenNodesDescription (int /*<<< orphan*/ ) ; 
 TYPE_2__* clusterLookupNode (scalar_t__) ; 
 int /*<<< orphan*/  clusterReset (int) ; 
 int clusterSaveConfig (int) ; 
 scalar_t__ clusterStartHandshake (scalar_t__,long long) ; 
 int /*<<< orphan*/  clusterUpdateReachableNodes () ; 
 int /*<<< orphan*/ * createObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictSize (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ getLongLongFromObject (TYPE_7__*,long long*) ; 
 TYPE_2__* myself ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 scalar_t__ sdslen (scalar_t__) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_5__ server ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 char* strerror (scalar_t__) ; 

void clusterCommand(client *c) {
    if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
        long long port;

        if (getLongLongFromObject(c->argv[3], &port) != C_OK) {
            addReplyErrorFormat(c,"Invalid TCP port specified: %s",
                                (char*)c->argv[3]->ptr);
            return;
        }

        if (clusterStartHandshake(c->argv[2]->ptr,port) == 0 &&
            errno == EINVAL)
        {
            addReplyErrorFormat(c,"Invalid node address specified: %s:%s",
                            (char*)c->argv[2]->ptr, (char*)c->argv[3]->ptr);
        } else {
            addReply(c,shared.ok);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
        /* CLUSTER NODES */
        robj *o;
        sds ci = clusterGenNodesDescription(0);

        o = createObject(OBJ_STRING,ci);
        addReplyBulk(c,o);
        decrRefCount(o);
    } else if (!strcasecmp(c->argv[1]->ptr,"myid") && c->argc == 2) {
        /* CLUSTER MYID */
        addReplyBulkCBuffer(c,myself->name, CLUSTER_NAMELEN);
    } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
        /* CLUSTER INFO */
        char *statestr[] = {"ok","fail","needhelp"};

        sds info = sdscatprintf(sdsempty(),
            "cluster_state:%s\r\n"
            "cluster_known_nodes:%lu\r\n"
            "cluster_reachable_nodes:%d\r\n"
            "cluster_size:%d\r\n"
            "cluster_stats_messages_sent:%lld\r\n"
            "cluster_stats_messages_received:%lld\r\n"
            , statestr[server.cluster->state],
            dictSize(server.cluster->nodes),
            server.cluster->reachable_nodes_count,
            server.cluster->size,
            server.cluster->stats_bus_messages_sent,
            server.cluster->stats_bus_messages_received
        );
        addReplyBulkSds(c, info);
    } else if (!strcasecmp(c->argv[1]->ptr,"saveconfig") && c->argc == 2) {
        int retval = clusterSaveConfig(1);

        if (retval == 0)
            addReply(c,shared.ok);
        else
            addReplyErrorFormat(c,"error saving the cluster node config: %s",
                strerror(errno));
    } else if (!strcasecmp(c->argv[1]->ptr,"forget") && c->argc == 3) {
        /* CLUSTER FORGET <NODE ID> */
        clusterNode *n;

        if (sdslen(c->argv[2]->ptr) != CLUSTER_NAMELEN) {
            addReplyError(c,"Invalid node identifier");
            return;
        }

        n = clusterLookupNode(c->argv[2]->ptr);

        if (!n) {
            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
            return;
        } else if (n == myself) {
            addReplyError(c,"I tried hard but I can't forget myself...");
            return;
        }
        clusterBlacklistAddNode(n);
        clusterDelNode(n);
        clusterUpdateReachableNodes();
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|
                             CLUSTER_TODO_SAVE_CONFIG);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"reset") &&
               (c->argc == 2 || c->argc == 3))
    {
        /* CLUSTER RESET [SOFT|HARD] */
        int hard = 0;

        /* Parse soft/hard argument. Default is soft. */
        if (c->argc == 3) {
            if (!strcasecmp(c->argv[2]->ptr,"hard")) {
                hard = 1;
            } else if (!strcasecmp(c->argv[2]->ptr,"soft")) {
                hard = 0;
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }

        clusterReset(hard);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"leaving") &&
               (c->argc == 2 || c->argc == 3))
    {
        /* CLUSTER LEAVING [yes|no] */
        if (c->argc == 3) {
            int oldflags = myself->flags;
            if (!strcasecmp(c->argv[2]->ptr,"yes")) {
                myself->flags |= CLUSTER_NODE_LEAVING;
                addReply(c,shared.ok);
            } else if (!strcasecmp(c->argv[2]->ptr,"no")) {
                myself->flags &= ~CLUSTER_NODE_LEAVING;
                addReply(c,shared.ok);
            } else {
                addReplyError(c,
                    "Wrong argument for CLUSTER LEAVING. Use 'yes' or 'no'");
            }
            if (oldflags != myself->flags)
                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
        } else {
            addReplySds(c,
                (myself->flags & CLUSTER_NODE_LEAVING) ?
                sdsnew("+yes\r\n") : sdsnew("+no\r\n")
            );
        }
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
}