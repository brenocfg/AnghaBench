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
struct bio {void* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_kcopyd_do_callback (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void full_bio_end_io(struct bio *bio, int error)
{
	void *callback_data = bio->bi_private;

	dm_kcopyd_do_callback(callback_data, 0, error ? 1 : 0);
}