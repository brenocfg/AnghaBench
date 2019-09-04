#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct oslog_stream_buf_entry_s {int dummy; } ;
struct firehose_tracepoint_s {int dummy; } ;
typedef  int /*<<< orphan*/  oslog_stream_link_type_t ;
typedef  TYPE_2__* oslog_stream_buf_entry_t ;
typedef  TYPE_3__* firehose_tracepoint_t ;
struct TYPE_10__ {int /*<<< orphan*/  ftid_value; } ;
typedef  TYPE_4__ firehose_tracepoint_id_u ;
struct TYPE_7__ {int /*<<< orphan*/  ftid_value; } ;
struct TYPE_9__ {size_t ft_length; int /*<<< orphan*/  ft_data; TYPE_1__ ft_id; int /*<<< orphan*/  ft_thread; } ;
struct TYPE_8__ {int size; TYPE_3__* metadata; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ kalloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static oslog_stream_buf_entry_t
oslog_stream_create_buf_entry(oslog_stream_link_type_t type, firehose_tracepoint_id_u ftid,
				uint64_t stamp, const void* pubdata, size_t publen)
{
	oslog_stream_buf_entry_t m_entry = NULL;
	firehose_tracepoint_t ft = NULL;
	size_t m_entry_len = 0;

	if (!pubdata) {
		return NULL;
	}

	m_entry_len = sizeof(struct oslog_stream_buf_entry_s) +
			sizeof(struct firehose_tracepoint_s) + publen;
	m_entry = (oslog_stream_buf_entry_t) kalloc(m_entry_len);
	if (!m_entry) {
		return NULL;
	}

	m_entry->type = type;
	m_entry->timestamp = stamp;
	m_entry->size = sizeof(struct firehose_tracepoint_s) + publen;

	ft = m_entry->metadata;
	ft->ft_thread = thread_tid(current_thread());
	ft->ft_id.ftid_value = ftid.ftid_value;
	ft->ft_length = publen;
	memcpy(ft->ft_data, pubdata, publen);

	return m_entry;
}