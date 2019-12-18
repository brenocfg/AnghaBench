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
struct gfs2_sbd {unsigned int sd_quota_chunks; unsigned char** sd_quota_bitmap; unsigned int sd_quota_slots; } ;
struct gfs2_quota_data {unsigned int qd_slot; int /*<<< orphan*/  qd_slot_count; TYPE_1__* qd_gl; } ;
struct TYPE_2__ {struct gfs2_sbd* gl_sbd; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  qd_lru_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int slot_get(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_sbd;
	unsigned int c, o = 0, b;
	unsigned char byte = 0;

	spin_lock(&qd_lru_lock);

	if (qd->qd_slot_count++) {
		spin_unlock(&qd_lru_lock);
		return 0;
	}

	for (c = 0; c < sdp->sd_quota_chunks; c++)
		for (o = 0; o < PAGE_SIZE; o++) {
			byte = sdp->sd_quota_bitmap[c][o];
			if (byte != 0xFF)
				goto found;
		}

	goto fail;

found:
	for (b = 0; b < 8; b++)
		if (!(byte & (1 << b)))
			break;
	qd->qd_slot = c * (8 * PAGE_SIZE) + o * 8 + b;

	if (qd->qd_slot >= sdp->sd_quota_slots)
		goto fail;

	sdp->sd_quota_bitmap[c][o] |= 1 << b;

	spin_unlock(&qd_lru_lock);

	return 0;

fail:
	qd->qd_slot_count--;
	spin_unlock(&qd_lru_lock);
	return -ENOSPC;
}