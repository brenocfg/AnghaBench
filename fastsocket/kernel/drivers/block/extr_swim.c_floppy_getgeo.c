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
struct hd_geometry {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct floppy_struct {int /*<<< orphan*/  track; int /*<<< orphan*/  sect; int /*<<< orphan*/  head; } ;
struct floppy_state {int dummy; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct floppy_state* private_data; } ;

/* Variables and functions */
 int get_floppy_geometry (struct floppy_state*,int /*<<< orphan*/ ,struct floppy_struct**) ; 

__attribute__((used)) static int floppy_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct floppy_state *fs = bdev->bd_disk->private_data;
	struct floppy_struct *g;
	int ret;

	ret = get_floppy_geometry(fs, 0, &g);
	if (ret)
		return ret;

	geo->heads = g->head;
	geo->sectors = g->sect;
	geo->cylinders = g->track;

	return 0;
}