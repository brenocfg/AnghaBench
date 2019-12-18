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
struct geom {int dummy; } ;
struct r10conf {scalar_t__ reshape_progress; struct geom prev; TYPE_1__* mddev; struct geom geo; } ;
struct r10bio {scalar_t__ sector; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int reshape_backwards; } ;

/* Variables and functions */
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  R10BIO_Previous ; 
 int /*<<< orphan*/  __raid10_find_phys (struct geom*,struct r10bio*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid10_find_phys(struct r10conf *conf, struct r10bio *r10bio)
{
	struct geom *geo = &conf->geo;

	if (conf->reshape_progress != MaxSector &&
	    ((r10bio->sector >= conf->reshape_progress) !=
	     conf->mddev->reshape_backwards)) {
		set_bit(R10BIO_Previous, &r10bio->state);
		geo = &conf->prev;
	} else
		clear_bit(R10BIO_Previous, &r10bio->state);

	__raid10_find_phys(geo, r10bio);
}