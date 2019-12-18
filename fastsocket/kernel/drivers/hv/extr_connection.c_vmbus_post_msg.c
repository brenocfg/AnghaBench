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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
union hv_connection_id {TYPE_1__ u; scalar_t__ asu32; } ;

/* Variables and functions */
 int HV_STATUS_INSUFFICIENT_BUFFERS ; 
 int /*<<< orphan*/  VMBUS_MESSAGE_CONNECTION_ID ; 
 int hv_post_message (union hv_connection_id,int,void*,size_t) ; 
 int /*<<< orphan*/  msleep (int) ; 

int vmbus_post_msg(void *buffer, size_t buflen)
{
	union hv_connection_id conn_id;
	int ret = 0;
	int retries = 0;

	conn_id.asu32 = 0;
	conn_id.u.id = VMBUS_MESSAGE_CONNECTION_ID;

	/*
	 * hv_post_message() can have transient failures because of
	 * insufficient resources. Retry the operation a couple of
	 * times before giving up.
	 */
	while (retries < 3) {
		ret =  hv_post_message(conn_id, 1, buffer, buflen);
		if (ret != HV_STATUS_INSUFFICIENT_BUFFERS)
			return ret;
		retries++;
		msleep(100);
	}
	return ret;
}