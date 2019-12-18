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
struct bio_set {scalar_t__ bio_integrity_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 

void bioset_integrity_free(struct bio_set *bs)
{
	if (bs->bio_integrity_pool)
		mempool_destroy(bs->bio_integrity_pool);
}