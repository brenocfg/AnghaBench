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
 int /*<<< orphan*/  BIO_RW_SYNCIO ; 
 scalar_t__ READ ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_rw_flagged (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool cfq_bio_sync(struct bio *bio)
{
	return bio_data_dir(bio) == READ || bio_rw_flagged(bio, BIO_RW_SYNCIO);
}