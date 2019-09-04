#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  clusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_GOTACK ; 
 int /*<<< orphan*/  clusterSendJobIDMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

void clusterSendGotAck(clusterNode *node, char *jobid, int known) {
    clusterSendJobIDMessage(CLUSTERMSG_TYPE_GOTACK,node,jobid,known);
}