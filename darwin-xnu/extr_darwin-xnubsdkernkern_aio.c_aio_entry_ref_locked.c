#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ aio_refcount; } ;
typedef  TYPE_1__ aio_workq_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_AIO_ENTRY_LOCK_OWNED (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void		
aio_entry_ref_locked(aio_workq_entry *entryp)
{
	ASSERT_AIO_ENTRY_LOCK_OWNED(entryp);

	if (entryp->aio_refcount < 0) {
		panic("AIO workq entry with a negative refcount.\n");
	}
	entryp->aio_refcount++;
}