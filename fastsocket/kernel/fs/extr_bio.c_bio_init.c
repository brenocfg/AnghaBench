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
struct bio {int bi_flags; int bi_comp_cpu; int /*<<< orphan*/  bi_cnt; } ;

/* Variables and functions */
 int BIO_UPTODATE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct bio*,int /*<<< orphan*/ ,int) ; 

void bio_init(struct bio *bio)
{
	memset(bio, 0, sizeof(*bio));
	bio->bi_flags = 1 << BIO_UPTODATE;
	bio->bi_comp_cpu = -1;
	atomic_set(&bio->bi_cnt, 1);
}