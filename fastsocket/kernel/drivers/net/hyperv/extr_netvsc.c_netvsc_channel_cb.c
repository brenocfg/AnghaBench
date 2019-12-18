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
struct vmpacket_descriptor {int type; } ;
struct netvsc_device {struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETVSC_PACKET_SIZE ; 
#define  VM_PKT_COMP 129 
#define  VM_PKT_DATA_USING_XFER_PAGES 128 
 struct netvsc_device* get_inbound_net_device (struct hv_device*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,...) ; 
 int /*<<< orphan*/  netvsc_receive (struct hv_device*,struct vmpacket_descriptor*) ; 
 int /*<<< orphan*/  netvsc_send_completion (struct hv_device*,struct vmpacket_descriptor*) ; 
 int vmbus_recvpacket_raw (int /*<<< orphan*/ ,unsigned char*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netvsc_channel_cb(void *context)
{
	int ret;
	struct hv_device *device = context;
	struct netvsc_device *net_device;
	u32 bytes_recvd;
	u64 request_id;
	unsigned char *packet;
	struct vmpacket_descriptor *desc;
	unsigned char *buffer;
	int bufferlen = NETVSC_PACKET_SIZE;
	struct net_device *ndev;

	packet = kzalloc(NETVSC_PACKET_SIZE * sizeof(unsigned char),
			 GFP_ATOMIC);
	if (!packet)
		return;
	buffer = packet;

	net_device = get_inbound_net_device(device);
	if (!net_device)
		goto out;
	ndev = net_device->ndev;

	do {
		ret = vmbus_recvpacket_raw(device->channel, buffer, bufferlen,
					   &bytes_recvd, &request_id);
		if (ret == 0) {
			if (bytes_recvd > 0) {
				desc = (struct vmpacket_descriptor *)buffer;
				switch (desc->type) {
				case VM_PKT_COMP:
					netvsc_send_completion(device, desc);
					break;

				case VM_PKT_DATA_USING_XFER_PAGES:
					netvsc_receive(device, desc);
					break;

				default:
					netdev_err(ndev,
						   "unhandled packet type %d, "
						   "tid %llx len %d\n",
						   desc->type, request_id,
						   bytes_recvd);
					break;
				}

				/* reset */
				if (bufferlen > NETVSC_PACKET_SIZE) {
					kfree(buffer);
					buffer = packet;
					bufferlen = NETVSC_PACKET_SIZE;
				}
			} else {
				/* reset */
				if (bufferlen > NETVSC_PACKET_SIZE) {
					kfree(buffer);
					buffer = packet;
					bufferlen = NETVSC_PACKET_SIZE;
				}

				break;
			}
		} else if (ret == -ENOBUFS) {
			/* Handle large packet */
			buffer = kmalloc(bytes_recvd, GFP_ATOMIC);
			if (buffer == NULL) {
				/* Try again next time around */
				netdev_err(ndev,
					   "unable to allocate buffer of size "
					   "(%d)!!\n", bytes_recvd);
				break;
			}

			bufferlen = bytes_recvd;
		}
	} while (1);

out:
	kfree(buffer);
	return;
}