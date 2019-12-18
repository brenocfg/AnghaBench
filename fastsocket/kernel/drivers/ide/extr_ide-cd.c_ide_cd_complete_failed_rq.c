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
struct request {int /*<<< orphan*/  sense_len; scalar_t__ sense; int /*<<< orphan*/  bio; scalar_t__ special; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EIO ; 
 void* bio_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  cdrom_analyze_sense_data (int /*<<< orphan*/ *,struct request*) ; 
 scalar_t__ ide_end_rq (int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 

__attribute__((used)) static void ide_cd_complete_failed_rq(ide_drive_t *drive, struct request *rq)
{
	/*
	 * For REQ_TYPE_SENSE, "rq->special" points to the original
	 * failed request.  Also, the sense data should be read
	 * directly from rq which might be different from the original
	 * sense buffer if it got copied during mapping.
	 */
	struct request *failed = (struct request *)rq->special;
	void *sense = bio_data(rq->bio);

	if (failed) {
		if (failed->sense) {
			/*
			 * Sense is always read into drive->sense_data.
			 * Copy back if the failed request has its
			 * sense pointer set.
			 */
			memcpy(failed->sense, sense, 18);
			failed->sense_len = rq->sense_len;
		}
		cdrom_analyze_sense_data(drive, failed);

		if (ide_end_rq(drive, failed, -EIO, blk_rq_bytes(failed)))
			BUG();
	} else
		cdrom_analyze_sense_data(drive, NULL);
}