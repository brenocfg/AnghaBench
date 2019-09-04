#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_seqno_t ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_5__ {int /*<<< orphan*/  imq_seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  imq_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_1__*) ; 

void
ipc_mqueue_set_seqno(
	ipc_mqueue_t		mqueue,
	mach_port_seqno_t	seqno)
{
	imq_lock(mqueue);
	mqueue->imq_seqno = seqno;
	imq_unlock(mqueue);
}