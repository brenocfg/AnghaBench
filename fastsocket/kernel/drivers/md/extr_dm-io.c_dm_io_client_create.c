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
struct dm_io_client {scalar_t__ pool; int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dm_io_client* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIN_BIOS ; 
 int /*<<< orphan*/  MIN_IOS ; 
 int /*<<< orphan*/  _dm_io_cache ; 
 int /*<<< orphan*/  bioset_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_io_client*) ; 
 struct dm_io_client* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mempool_create_slab_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 

struct dm_io_client *dm_io_client_create(void)
{
	struct dm_io_client *client;

	client = kmalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return ERR_PTR(-ENOMEM);

	client->pool = mempool_create_slab_pool(MIN_IOS, _dm_io_cache);
	if (!client->pool)
		goto bad;

	client->bios = bioset_create(MIN_BIOS, 0);
	if (!client->bios)
		goto bad;

	return client;

   bad:
	if (client->pool)
		mempool_destroy(client->pool);
	kfree(client);
	return ERR_PTR(-ENOMEM);
}