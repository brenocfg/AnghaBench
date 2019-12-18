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
struct mddev {int /*<<< orphan*/  bio_set; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_free (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mddev_bio_destructor(struct bio *bio)
{
	struct mddev *mddev, **mddevp;

	mddevp = (void*)bio;
	mddev = mddevp[-1];

	bio_free(bio, mddev->bio_set);
}