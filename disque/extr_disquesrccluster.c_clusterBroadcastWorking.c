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
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  nodes_delivered; } ;
typedef  TYPE_1__ job ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_NOFLAGS ; 
 int /*<<< orphan*/  CLUSTERMSG_TYPE_WORKING ; 
 int /*<<< orphan*/  JOB_ID_LEN ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  clusterBroadcastJobIDMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clusterBroadcastWorking(job *j) {
    serverLog(LL_VERBOSE,"BCAST WORKING: %.*s",JOB_ID_LEN,j->id);
    clusterBroadcastJobIDMessage(j->nodes_delivered,j->id,
                                 CLUSTERMSG_TYPE_WORKING,0,CLUSTERMSG_NOFLAGS);
}