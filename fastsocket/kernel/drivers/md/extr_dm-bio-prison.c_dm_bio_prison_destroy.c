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
struct dm_bio_prison {int /*<<< orphan*/  cell_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dm_bio_prison*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

void dm_bio_prison_destroy(struct dm_bio_prison *prison)
{
	mempool_destroy(prison->cell_pool);
	kfree(prison);
}