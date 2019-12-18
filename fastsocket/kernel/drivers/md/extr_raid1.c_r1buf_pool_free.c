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
struct r1bio {TYPE_2__** bios; } ;
struct pool_info {int raid_disks; } ;
struct TYPE_4__ {TYPE_1__* bi_io_vec; } ;
struct TYPE_3__ {scalar_t__ bv_page; } ;

/* Variables and functions */
 int RESYNC_PAGES ; 
 int /*<<< orphan*/  bio_put (TYPE_2__*) ; 
 int /*<<< orphan*/  r1bio_pool_free (struct r1bio*,void*) ; 
 int /*<<< orphan*/  safe_put_page (scalar_t__) ; 

__attribute__((used)) static void r1buf_pool_free(void *__r1_bio, void *data)
{
	struct pool_info *pi = data;
	int i,j;
	struct r1bio *r1bio = __r1_bio;

	for (i = 0; i < RESYNC_PAGES; i++)
		for (j = pi->raid_disks; j-- ;) {
			if (j == 0 ||
			    r1bio->bios[j]->bi_io_vec[i].bv_page !=
			    r1bio->bios[0]->bi_io_vec[i].bv_page)
				safe_put_page(r1bio->bios[j]->bi_io_vec[i].bv_page);
		}
	for (i=0 ; i < pi->raid_disks; i++)
		bio_put(r1bio->bios[i]);

	r1bio_pool_free(r1bio, data);
}