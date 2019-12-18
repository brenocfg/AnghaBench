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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct vmpacket_descriptor {int len8; int /*<<< orphan*/  trans_id; } ;
struct vmbus_channel {int /*<<< orphan*/  inbound; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int hv_ringbuffer_peek (int /*<<< orphan*/ *,struct vmpacket_descriptor*,int) ; 
 int hv_ringbuffer_read (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  vmbus_setevent (struct vmbus_channel*) ; 

int vmbus_recvpacket_raw(struct vmbus_channel *channel, void *buffer,
			      u32 bufferlen, u32 *buffer_actual_len,
			      u64 *requestid)
{
	struct vmpacket_descriptor desc;
	u32 packetlen;
	int ret;
	bool signal = false;

	*buffer_actual_len = 0;
	*requestid = 0;


	ret = hv_ringbuffer_peek(&channel->inbound, &desc,
			     sizeof(struct vmpacket_descriptor));
	if (ret != 0)
		return 0;


	packetlen = desc.len8 << 3;

	*buffer_actual_len = packetlen;

	if (packetlen > bufferlen) {
		pr_err("Buffer too small - needed %d bytes but "
			"got space for only %d bytes\n",
			packetlen, bufferlen);
		return -ENOBUFS;
	}

	*requestid = desc.trans_id;

	/* Copy over the entire packet to the user buffer */
	ret = hv_ringbuffer_read(&channel->inbound, buffer, packetlen, 0,
				 &signal);

	if (signal)
		vmbus_setevent(channel);

	return 0;
}