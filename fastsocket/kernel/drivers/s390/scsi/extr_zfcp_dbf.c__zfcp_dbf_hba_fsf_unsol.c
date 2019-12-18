#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status_type; int payload_size; int /*<<< orphan*/  payload; int /*<<< orphan*/  queue_designator; int /*<<< orphan*/  status_subtype; int /*<<< orphan*/  failed; } ;
struct TYPE_6__ {TYPE_2__ status; } ;
struct zfcp_dbf_hba_record {TYPE_3__ u; int /*<<< orphan*/  tag2; int /*<<< orphan*/  tag; } ;
struct zfcp_dbf {int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  hba; TYPE_1__* adapter; struct zfcp_dbf_hba_record hba_buf; } ;
struct fsf_status_read_buffer {int status_type; int /*<<< orphan*/  payload; int /*<<< orphan*/  status_subtype; int /*<<< orphan*/  queue_designator; } ;
struct fsf_queue_designator {int dummy; } ;
struct fsf_link_down_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat_miss; } ;

/* Variables and functions */
#define  FSF_STATUS_READ_BIT_ERROR_THRESHOLD 133 
#define  FSF_STATUS_READ_FEATURE_UPDATE_ALERT 132 
#define  FSF_STATUS_READ_LINK_DOWN 131 
#define  FSF_STATUS_READ_SENSE_DATA_AVAIL 130 
#define  FSF_STATUS_READ_SUB_FDISC_FAILED 129 
#define  FSF_STATUS_READ_SUB_NO_PHYSICAL_LINK 128 
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 int ZFCP_DBF_UNSOL_PAYLOAD_BIT_ERROR_THRESHOLD ; 
 int ZFCP_DBF_UNSOL_PAYLOAD_FEATURE_UPDATE_ALERT ; 
 int ZFCP_DBF_UNSOL_PAYLOAD_SENSE_DATA_AVAIL ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,struct zfcp_dbf_hba_record*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_hba_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void _zfcp_dbf_hba_fsf_unsol(const char *tag, int level, struct zfcp_dbf *dbf,
			     struct fsf_status_read_buffer *status_buffer)
{
	struct zfcp_dbf_hba_record *rec = &dbf->hba_buf;
	unsigned long flags;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	memset(rec, 0, sizeof(*rec));
	strncpy(rec->tag, "stat", ZFCP_DBF_TAG_SIZE);
	strncpy(rec->tag2, tag, ZFCP_DBF_TAG_SIZE);

	rec->u.status.failed = atomic_read(&dbf->adapter->stat_miss);
	if (status_buffer != NULL) {
		rec->u.status.status_type = status_buffer->status_type;
		rec->u.status.status_subtype = status_buffer->status_subtype;
		memcpy(&rec->u.status.queue_designator,
		       &status_buffer->queue_designator,
		       sizeof(struct fsf_queue_designator));

		switch (status_buffer->status_type) {
		case FSF_STATUS_READ_SENSE_DATA_AVAIL:
			rec->u.status.payload_size =
			    ZFCP_DBF_UNSOL_PAYLOAD_SENSE_DATA_AVAIL;
			break;

		case FSF_STATUS_READ_BIT_ERROR_THRESHOLD:
			rec->u.status.payload_size =
			    ZFCP_DBF_UNSOL_PAYLOAD_BIT_ERROR_THRESHOLD;
			break;

		case FSF_STATUS_READ_LINK_DOWN:
			switch (status_buffer->status_subtype) {
			case FSF_STATUS_READ_SUB_NO_PHYSICAL_LINK:
			case FSF_STATUS_READ_SUB_FDISC_FAILED:
				rec->u.status.payload_size =
					sizeof(struct fsf_link_down_info);
			}
			break;

		case FSF_STATUS_READ_FEATURE_UPDATE_ALERT:
			rec->u.status.payload_size =
			    ZFCP_DBF_UNSOL_PAYLOAD_FEATURE_UPDATE_ALERT;
			break;
		}
		memcpy(&rec->u.status.payload,
		       &status_buffer->payload, rec->u.status.payload_size);
	}

	debug_event(dbf->hba, level, rec, sizeof(*rec));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
}