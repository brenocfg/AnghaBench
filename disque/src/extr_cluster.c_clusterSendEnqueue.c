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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ job ;
typedef  int /*<<< orphan*/  clusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_ENQUEUE ; 
 int /*<<< orphan*/  clusterSendJobIDMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clusterSendEnqueue(clusterNode *node, job *j, uint32_t delay) {
    clusterSendJobIDMessage(CLUSTERMSG_TYPE_ENQUEUE,node,j->id,delay);
}