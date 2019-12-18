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
struct mirror {TYPE_1__* dev; } ;
struct bio {int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_sector (struct mirror*,struct bio*) ; 

__attribute__((used)) static void map_bio(struct mirror *m, struct bio *bio)
{
	bio->bi_bdev = m->dev->bdev;
	bio->bi_sector = map_sector(m, bio);
}