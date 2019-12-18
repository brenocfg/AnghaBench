#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* inuse; } ;
typedef  TYPE_2__ WFC_WAITER_T ;
struct TYPE_8__ {int /*<<< orphan*/  sem; } ;
struct TYPE_10__ {TYPE_1__ waitpool; } ;
typedef  TYPE_3__ WFC_CLIENT_IPC_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  vcos_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wfc_client_ipc_release_waiter(WFC_CLIENT_IPC_T *client, WFC_WAITER_T *waiter)
{
   vcos_log_trace("%s: at %p", VCOS_FUNCTION, waiter);

   vcos_assert(waiter);
   vcos_assert(waiter->inuse);

   waiter->inuse = 0;
   vcos_semaphore_post(&client->waitpool.sem);
}