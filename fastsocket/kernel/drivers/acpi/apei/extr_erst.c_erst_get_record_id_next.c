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
struct TYPE_2__ {int len; scalar_t__* entries; int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ APEI_ERST_INVALID_RECORD_ID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int __erst_record_id_cache_add_one () ; 
 scalar_t__ erst_disable ; 
 TYPE_1__ erst_record_id_cache ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int erst_get_record_id_next(int *pos, u64 *record_id)
{
	int rc = 0;
	u64 *entries;

	if (erst_disable)
		return -ENODEV;

	/* must be enclosed by erst_get_record_id_begin/end */
	BUG_ON(!erst_record_id_cache.refcount);
	BUG_ON(*pos < 0 || *pos > erst_record_id_cache.len);

	mutex_lock(&erst_record_id_cache.lock);
	entries = erst_record_id_cache.entries;
	for (; *pos < erst_record_id_cache.len; (*pos)++)
		if (entries[*pos] != APEI_ERST_INVALID_RECORD_ID)
			break;
	/* found next record id in cache */
	if (*pos < erst_record_id_cache.len) {
		*record_id = entries[*pos];
		(*pos)++;
		goto out_unlock;
	}

	/* Try to add one more record ID to cache */
	rc = __erst_record_id_cache_add_one();
	if (rc < 0)
		goto out_unlock;
	/* successfully add one new ID */
	if (rc == 1) {
		*record_id = erst_record_id_cache.entries[*pos];
		(*pos)++;
		rc = 0;
	} else {
		*pos = -1;
		*record_id = APEI_ERST_INVALID_RECORD_ID;
	}
out_unlock:
	mutex_unlock(&erst_record_id_cache.lock);

	return rc;
}