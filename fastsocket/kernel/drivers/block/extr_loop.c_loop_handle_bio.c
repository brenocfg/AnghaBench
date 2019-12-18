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
struct loop_device {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_private; int /*<<< orphan*/  bi_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int do_bio_filebacked (struct loop_device*,struct bio*) ; 
 int /*<<< orphan*/  do_loop_switch (struct loop_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void loop_handle_bio(struct loop_device *lo, struct bio *bio)
{
	if (unlikely(!bio->bi_bdev)) {
		do_loop_switch(lo, bio->bi_private);
		bio_put(bio);
	} else {
		int ret = do_bio_filebacked(lo, bio);
		bio_endio(bio, ret);
	}
}