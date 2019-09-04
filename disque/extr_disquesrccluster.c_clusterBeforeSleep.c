#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cluster; } ;
struct TYPE_3__ {int todo_before_sleep; } ;

/* Variables and functions */
 int CLUSTER_TODO_FSYNC_CONFIG ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 int /*<<< orphan*/  clusterSaveConfigOrDie (int) ; 
 int /*<<< orphan*/  clusterUpdateState () ; 
 TYPE_2__ server ; 

void clusterBeforeSleep(void) {
    /* Update the cluster state. */
    if (server.cluster->todo_before_sleep & CLUSTER_TODO_UPDATE_STATE)
        clusterUpdateState();

    /* Save the config, possibly using fsync. */
    if (server.cluster->todo_before_sleep & CLUSTER_TODO_SAVE_CONFIG) {
        int fsync = server.cluster->todo_before_sleep &
                    CLUSTER_TODO_FSYNC_CONFIG;
        clusterSaveConfigOrDie(fsync);
    }

    /* Reset our flags (not strictly needed since every single function
     * called for flags set should be able to clear its flag). */
    server.cluster->todo_before_sleep = 0;
}