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
struct vmbus_channel_msginfo {int dummy; } ;
struct vmbus_channel_initiate_contact {int dummy; } ;
typedef  int __u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * monitor_pages; int /*<<< orphan*/ * int_page; scalar_t__ work_queue; int /*<<< orphan*/  conn_state; void* send_int_page; int /*<<< orphan*/ * recv_int_page; int /*<<< orphan*/  channel_lock; int /*<<< orphan*/  chn_list; int /*<<< orphan*/  channelmsg_lock; int /*<<< orphan*/  chn_msg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTING ; 
 int /*<<< orphan*/  DISCONNECTED ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int VERSION_CURRENT ; 
 int VERSION_INVAL ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int) ; 
 scalar_t__ create_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  host_info_eax ; 
 int host_info_ebx ; 
 int /*<<< orphan*/  host_info_ecx ; 
 int host_info_edx ; 
 int /*<<< orphan*/  kfree (struct vmbus_channel_msginfo*) ; 
 struct vmbus_channel_msginfo* kzalloc (int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ vmbus_connection ; 
 int vmbus_get_next_version (int) ; 
 int vmbus_negotiate_version (struct vmbus_channel_msginfo*,int) ; 
 int vmbus_proto_version ; 

int vmbus_connect(void)
{
	int ret = 0;
	struct vmbus_channel_msginfo *msginfo = NULL;
	__u32 version;

	/* Initialize the vmbus connection */
	vmbus_connection.conn_state = CONNECTING;
	vmbus_connection.work_queue = create_workqueue("hv_vmbus_con");
	if (!vmbus_connection.work_queue) {
		ret = -ENOMEM;
		goto cleanup;
	}

	INIT_LIST_HEAD(&vmbus_connection.chn_msg_list);
	spin_lock_init(&vmbus_connection.channelmsg_lock);

	INIT_LIST_HEAD(&vmbus_connection.chn_list);
	spin_lock_init(&vmbus_connection.channel_lock);

	/*
	 * Setup the vmbus event connection for channel interrupt
	 * abstraction stuff
	 */
	vmbus_connection.int_page =
	(void *)__get_free_pages(GFP_KERNEL|__GFP_ZERO, 0);
	if (vmbus_connection.int_page == NULL) {
		ret = -ENOMEM;
		goto cleanup;
	}

	vmbus_connection.recv_int_page = vmbus_connection.int_page;
	vmbus_connection.send_int_page =
		(void *)((unsigned long)vmbus_connection.int_page +
			(PAGE_SIZE >> 1));

	/*
	 * Setup the monitor notification facility. The 1st page for
	 * parent->child and the 2nd page for child->parent
	 */
	vmbus_connection.monitor_pages =
	(void *)__get_free_pages((GFP_KERNEL|__GFP_ZERO), 1);
	if (vmbus_connection.monitor_pages == NULL) {
		ret = -ENOMEM;
		goto cleanup;
	}

	msginfo = kzalloc(sizeof(*msginfo) +
			  sizeof(struct vmbus_channel_initiate_contact),
			  GFP_KERNEL);
	if (msginfo == NULL) {
		ret = -ENOMEM;
		goto cleanup;
	}

	/*
	 * Negotiate a compatible VMBUS version number with the
	 * host. We start with the highest number we can support
	 * and work our way down until we negotiate a compatible
	 * version.
	 */

	version = VERSION_CURRENT;

	do {
		ret = vmbus_negotiate_version(msginfo, version);
		if (ret == 0)
			break;

		version = vmbus_get_next_version(version);
	} while (version != VERSION_INVAL);

	if (version == VERSION_INVAL)
		goto cleanup;

	vmbus_proto_version = version;
	pr_info("Hyper-V Host Build:%d-%d.%d-%d-%d.%d; Vmbus version:%d.%d\n",
		    host_info_eax, host_info_ebx >> 16,
		    host_info_ebx & 0xFFFF, host_info_ecx,
		    host_info_edx >> 24, host_info_edx & 0xFFFFFF,
		    version >> 16, version & 0xFFFF);

	kfree(msginfo);
	return 0;

cleanup:
	pr_err("Unable to connect to host\n");
	vmbus_connection.conn_state = DISCONNECTED;

	if (vmbus_connection.work_queue)
		destroy_workqueue(vmbus_connection.work_queue);

	if (vmbus_connection.int_page) {
		free_pages((unsigned long)vmbus_connection.int_page, 0);
		vmbus_connection.int_page = NULL;
	}

	if (vmbus_connection.monitor_pages) {
		free_pages((unsigned long)vmbus_connection.monitor_pages, 1);
		vmbus_connection.monitor_pages = NULL;
	}

	kfree(msginfo);

	return ret;
}