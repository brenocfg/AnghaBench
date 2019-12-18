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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct MPT3SAS_ADAPTER {int dummy; } ;
typedef  int /*<<< orphan*/  Mpi2EventNotificationReply_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mpt3sas_base_get_reply_virt_addr (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_ctl_add_to_event_log (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *) ; 

u8
mpt3sas_ctl_event_callback(struct MPT3SAS_ADAPTER *ioc, u8 msix_index,
	u32 reply)
{
	Mpi2EventNotificationReply_t *mpi_reply;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	mpt3sas_ctl_add_to_event_log(ioc, mpi_reply);
	return 1;
}