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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ READ ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int bio_integrity_tag (struct bio*,void*,unsigned int,int /*<<< orphan*/ ) ; 

int bio_integrity_get_tag(struct bio *bio, void *tag_buf, unsigned int len)
{
	BUG_ON(bio_data_dir(bio) != READ);

	return bio_integrity_tag(bio, tag_buf, len, 0);
}