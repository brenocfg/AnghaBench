#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ head; scalar_t__ active_record_count; scalar_t__ freelist_records; scalar_t__ tail; } ;
typedef  TYPE_1__ btlog_t ;
typedef  scalar_t__ btlog_recordindex_t ;
struct TYPE_7__ {scalar_t__ next; scalar_t__ bthash; int /*<<< orphan*/  element_record_queue; } ;
typedef  TYPE_2__ btlog_record_t ;

/* Variables and functions */
 scalar_t__ BTLOG_RECORDINDEX_NONE ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* lookup_btrecord (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
btlog_add_record_to_freelist(btlog_t *btlog, btlog_recordindex_t recindex)
{
	btlog_recordindex_t precindex = BTLOG_RECORDINDEX_NONE;
	btlog_record_t *precord = NULL, *record = NULL;

	record = lookup_btrecord(btlog, recindex);

	assert(TAILQ_EMPTY(&record->element_record_queue));

	record->bthash = 0;

	precindex = btlog->head;
	precord = lookup_btrecord(btlog, precindex);

	if (precindex == recindex) {
		btlog->head = precord->next;
		btlog->active_record_count--;

		record->next = btlog->freelist_records;
		btlog->freelist_records = recindex;
	
		if (btlog->head == BTLOG_RECORDINDEX_NONE) {
			/* active list is now empty, update tail */
			btlog->tail = BTLOG_RECORDINDEX_NONE;
			assert(btlog->active_record_count == 0);
		}
	} else {
		while (precindex != BTLOG_RECORDINDEX_NONE) {
			if (precord->next == recindex) {
				precord->next = record->next;
				btlog->active_record_count--;

				record->next = btlog->freelist_records;
				btlog->freelist_records = recindex;

				if (btlog->tail == recindex) {
					btlog->tail = precindex;
				}
				break;
			} else {
				precindex = precord->next;
				precord = lookup_btrecord(btlog, precindex);
			}
		}
	}
}