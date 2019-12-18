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
struct r1conf {scalar_t__ next_resync; int /*<<< orphan*/  r1buf_pool; int /*<<< orphan*/  poolinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int RESYNC_BLOCK_SIZE ; 
 int RESYNC_WINDOW ; 
 int /*<<< orphan*/  mempool_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r1buf_pool_alloc ; 
 int /*<<< orphan*/  r1buf_pool_free ; 

__attribute__((used)) static int init_resync(struct r1conf *conf)
{
	int buffs;

	buffs = RESYNC_WINDOW / RESYNC_BLOCK_SIZE;
	BUG_ON(conf->r1buf_pool);
	conf->r1buf_pool = mempool_create(buffs, r1buf_pool_alloc, r1buf_pool_free,
					  conf->poolinfo);
	if (!conf->r1buf_pool)
		return -ENOMEM;
	conf->next_resync = 0;
	return 0;
}