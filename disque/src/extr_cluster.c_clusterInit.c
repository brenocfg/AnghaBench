#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  clusterState ;
struct TYPE_8__ {int port; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int cfd_count; int port; int /*<<< orphan*/ * cfd; int /*<<< orphan*/  el; TYPE_1__* cluster; int /*<<< orphan*/  cluster_configfile; } ;
struct TYPE_6__ {int size; TYPE_3__* myself; scalar_t__ reachable_nodes_count; int /*<<< orphan*/ * reachable_nodes; scalar_t__ stats_bus_messages_received; scalar_t__ stats_bus_messages_sent; void* nodes_black_list; void* deleted_nodes; void* nodes; scalar_t__ todo_before_sleep; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  CLUSTER_NODE_MYSELF ; 
 int /*<<< orphan*/  CLUSTER_OK ; 
 int CLUSTER_PORT_INCR ; 
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterAcceptHandler ; 
 int /*<<< orphan*/  clusterAddNode (TYPE_3__*) ; 
 scalar_t__ clusterLoadConfig (int /*<<< orphan*/ ) ; 
 scalar_t__ clusterLockConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterNodesBlackListDictType ; 
 int /*<<< orphan*/  clusterNodesDictType ; 
 int /*<<< orphan*/  clusterSaveConfigOrDie (int) ; 
 int /*<<< orphan*/  clusterUpdateReachableNodes () ; 
 int /*<<< orphan*/  clusterUpdateState () ; 
 TYPE_3__* createClusterNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ listenToPort (int,int /*<<< orphan*/ *,int*) ; 
 TYPE_3__* myself ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_1__* zmalloc (int) ; 

void clusterInit(void) {
    int saveconf = 0;

    server.cluster = zmalloc(sizeof(clusterState));
    server.cluster->myself = NULL;
    server.cluster->state = CLUSTER_OK;
    server.cluster->size = 1;
    server.cluster->todo_before_sleep = 0;
    server.cluster->nodes = dictCreate(&clusterNodesDictType,NULL);
    server.cluster->deleted_nodes = dictCreate(&clusterNodesDictType,NULL);
    server.cluster->nodes_black_list =
        dictCreate(&clusterNodesBlackListDictType,NULL);
    server.cluster->stats_bus_messages_sent = 0;
    server.cluster->stats_bus_messages_received = 0;
    server.cluster->reachable_nodes = NULL;
    server.cluster->reachable_nodes_count = 0;

    /* Lock the cluster config file to make sure every node uses
     * its own nodes.conf. */
    if (clusterLockConfig(server.cluster_configfile) == C_ERR)
        exit(1);

    /* Load or create a new nodes configuration. */
    if (clusterLoadConfig(server.cluster_configfile) == C_ERR) {
        /* No configuration found. We will just use the random name provided
         * by the createClusterNode() function. */
        myself = server.cluster->myself =
            createClusterNode(NULL,CLUSTER_NODE_MYSELF);
        serverLog(LL_NOTICE,"No cluster configuration found, I'm %.40s",
            myself->name);
        clusterAddNode(myself);
        saveconf = 1;
    }
    if (saveconf) clusterSaveConfigOrDie(1);

    /* We need a listening TCP port for our cluster messaging needs. */
    server.cfd_count = 0;

    /* Port sanity check II
     * The other handshake port check is triggered too late to stop
     * us from trying to use a too-high cluster port number. */
    if (server.port > (65535-CLUSTER_PORT_INCR)) {
        serverLog(LL_WARNING, "Disque port number too high. "
                   "Cluster communication port is 10,000 port "
                   "numbers higher than your Disque node port. "
                   "Your Disque node port number must be "
                   "lower than 55535.");
        exit(1);
    }

    if (listenToPort(server.port+CLUSTER_PORT_INCR,
        server.cfd,&server.cfd_count) == C_ERR)
    {
        exit(1);
    } else {
        int j;

        for (j = 0; j < server.cfd_count; j++) {
            if (aeCreateFileEvent(server.el, server.cfd[j], AE_READABLE,
                clusterAcceptHandler, NULL) == AE_ERR)
                    serverPanic("Unrecoverable error creating Disque Cluster "
                                "Bus file event.");
        }
    }

    /* Set myself->port to my listening port, we'll just need to discover
     * the IP address via MEET messages. */
    myself->port = server.port;

    /* Update state and list of reachable nodes. */
    clusterUpdateState();
    clusterUpdateReachableNodes();
}