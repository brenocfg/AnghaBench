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
struct dm_io_client {int /*<<< orphan*/  bios; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_io_client*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

void dm_io_client_destroy(struct dm_io_client *client)
{
	mempool_destroy(client->pool);
	bioset_free(client->bios);
	kfree(client);
}