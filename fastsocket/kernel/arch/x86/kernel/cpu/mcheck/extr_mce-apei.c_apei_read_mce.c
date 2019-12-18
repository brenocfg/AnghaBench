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
typedef  scalar_t__ u64 ;
struct mce {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  creator_id; } ;
struct cper_mce_record {int /*<<< orphan*/  mce; TYPE_1__ hdr; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rcd ;

/* Variables and functions */
 scalar_t__ APEI_ERST_INVALID_RECORD_ID ; 
 int /*<<< orphan*/  CPER_CREATOR_MCE ; 
 int ENOENT ; 
 int erst_get_record_id_begin (int*) ; 
 int /*<<< orphan*/  erst_get_record_id_end () ; 
 int erst_get_record_id_next (int*,scalar_t__*) ; 
 int erst_read (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (struct mce*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ uuid_le_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t apei_read_mce(struct mce *m, u64 *record_id)
{
	struct cper_mce_record rcd;
	int rc, pos;

	rc = erst_get_record_id_begin(&pos);
	if (rc)
		return rc;
retry:
	rc = erst_get_record_id_next(&pos, record_id);
	if (rc)
		goto out;
	/* no more record */
	if (*record_id == APEI_ERST_INVALID_RECORD_ID)
		goto out;
	rc = erst_read(*record_id, &rcd.hdr, sizeof(rcd));
	/* someone else has cleared the record, try next one */
	if (rc == -ENOENT)
		goto retry;
	else if (rc < 0)
		goto out;
	/* try to skip other type records in storage */
	else if (rc != sizeof(rcd) ||
		 uuid_le_cmp(rcd.hdr.creator_id, CPER_CREATOR_MCE))
		goto retry;
	memcpy(m, &rcd.mce, sizeof(*m));
	rc = sizeof(*m);
out:
	erst_get_record_id_end();

	return rc;
}