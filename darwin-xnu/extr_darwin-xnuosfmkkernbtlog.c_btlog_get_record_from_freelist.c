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
struct TYPE_6__ {scalar_t__ freelist_records; } ;
typedef  TYPE_1__ btlog_t ;
typedef  scalar_t__ btlog_recordindex_t ;
struct TYPE_7__ {scalar_t__ next; } ;
typedef  TYPE_2__ btlog_record_t ;

/* Variables and functions */
 scalar_t__ BTLOG_RECORDINDEX_NONE ; 
 TYPE_2__* lookup_btrecord (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static btlog_recordindex_t
btlog_get_record_from_freelist(btlog_t *btlog)
{
	btlog_recordindex_t	recindex = btlog->freelist_records;

	if (recindex == BTLOG_RECORDINDEX_NONE) {
		/* nothing on freelist */
		return BTLOG_RECORDINDEX_NONE;
	} else {
		/* remove the head of the freelist_records */
		btlog_record_t *record = lookup_btrecord(btlog, recindex);
		btlog->freelist_records = record->next;
		return recindex;
	}
}