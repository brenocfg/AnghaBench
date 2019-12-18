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
struct raid10_info {int dummy; } ;
struct TYPE_2__ {int far_copies; int /*<<< orphan*/  far_offset; } ;
struct r10conf {scalar_t__ copies; int /*<<< orphan*/ * mirrors_new; TYPE_1__ geo; } ;
struct mddev {int array_sectors; int delta_disks; int raid_disks; struct r10conf* private; } ;
struct geom {int far_copies; int chunk_mask; int /*<<< orphan*/  far_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  enough (struct r10conf*,int) ; 
 int /*<<< orphan*/  geo_start ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ setup_geo (struct geom*,struct mddev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raid10_check_reshape(struct mddev *mddev)
{
	/* Called when there is a request to change
	 * - layout (to ->new_layout)
	 * - chunk size (to ->new_chunk_sectors)
	 * - raid_disks (by delta_disks)
	 * or when trying to restart a reshape that was ongoing.
	 *
	 * We need to validate the request and possibly allocate
	 * space if that might be an issue later.
	 *
	 * Currently we reject any reshape of a 'far' mode array,
	 * allow chunk size to change if new is generally acceptable,
	 * allow raid_disks to increase, and allow
	 * a switch between 'near' mode and 'offset' mode.
	 */
	struct r10conf *conf = mddev->private;
	struct geom geo;

	if (conf->geo.far_copies != 1 && !conf->geo.far_offset)
		return -EINVAL;

	if (setup_geo(&geo, mddev, geo_start) != conf->copies)
		/* mustn't change number of copies */
		return -EINVAL;
	if (geo.far_copies > 1 && !geo.far_offset)
		/* Cannot switch to 'far' mode */
		return -EINVAL;

	if (mddev->array_sectors & geo.chunk_mask)
			/* not factor of array size */
			return -EINVAL;

	if (!enough(conf, -1))
		return -EINVAL;

	kfree(conf->mirrors_new);
	conf->mirrors_new = NULL;
	if (mddev->delta_disks > 0) {
		/* allocate new 'mirrors' list */
		conf->mirrors_new = kzalloc(
			sizeof(struct raid10_info)
			*(mddev->raid_disks +
			  mddev->delta_disks),
			GFP_KERNEL);
		if (!conf->mirrors_new)
			return -ENOMEM;
	}
	return 0;
}