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
struct rdma_addr_client {int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_client (struct rdma_addr_client*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void rdma_addr_unregister_client(struct rdma_addr_client *client)
{
	put_client(client);
	wait_for_completion(&client->comp);
}