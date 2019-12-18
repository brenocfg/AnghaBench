#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aeEventLoop {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unblocked_clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (struct aeEventLoop*) ; 
 int /*<<< orphan*/  clusterBeforeSleep () ; 
 int /*<<< orphan*/  flushAppendOnlyFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handleClientsBlockedOnQueues () ; 
 int /*<<< orphan*/  handleClientsWithPendingWrites () ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processUnblockedClients () ; 
 TYPE_1__ server ; 

void beforeSleep(struct aeEventLoop *eventLoop) {
    UNUSED(eventLoop);

    /* Call the Cluster before sleep function. Note that this function
     * may change the state of Cluster, so it's a good idea to call it
     * before serving the unblocked clients later in this function. */
    clusterBeforeSleep();

    /* Unblock clients waiting to receive messages into queues.
     * We do this both on processCommand() and here, since we need to
     * unblock clients when queues are populated asynchronously. */
    handleClientsBlockedOnQueues();

    /* Try to process pending commands for clients that were just unblocked. */
    if (listLength(server.unblocked_clients))
        processUnblockedClients();

    /* Write the AOF buffer on disk */
    flushAppendOnlyFile(0);

    /* Handle writes with pending output buffers. */
    handleClientsWithPendingWrites();
}