#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bi_rw; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;
struct log_c {TYPE_2__ io_req; TYPE_1__ header_location; } ;
struct dm_io_region {int /*<<< orphan*/  count; int /*<<< orphan*/  sector; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_FLUSH ; 
 int dm_io (TYPE_2__*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flush_header(struct log_c *lc)
{
	struct dm_io_region null_location = {
		.bdev = lc->header_location.bdev,
		.sector = 0,
		.count = 0,
	};

	lc->io_req.bi_rw = WRITE_FLUSH;

	return dm_io(&lc->io_req, 1, &null_location, NULL);
}