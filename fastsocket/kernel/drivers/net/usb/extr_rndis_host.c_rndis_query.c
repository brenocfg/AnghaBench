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
typedef  int u32 ;
struct usbnet {int dummy; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct rndis_query_c {int /*<<< orphan*/  request_id; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; } ;
struct rndis_query {void* offset; void* len; int /*<<< orphan*/  oid; void* msg_len; int /*<<< orphan*/  msg_type; } ;
struct rndis_msg_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CONTROL_BUFFER_SIZE ; 
 int EDOM ; 
 int /*<<< orphan*/  RNDIS_MSG_QUERY ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rndis_query*,int /*<<< orphan*/ ,int) ; 
 int rndis_command (struct usbnet*,struct rndis_msg_hdr*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rndis_query(struct usbnet *dev, struct usb_interface *intf,
		void *buf, __le32 oid, u32 in_len,
		void **reply, int *reply_len)
{
	int retval;
	union {
		void			*buf;
		struct rndis_msg_hdr	*header;
		struct rndis_query	*get;
		struct rndis_query_c	*get_c;
	} u;
	u32 off, len;

	u.buf = buf;

	memset(u.get, 0, sizeof *u.get + in_len);
	u.get->msg_type = RNDIS_MSG_QUERY;
	u.get->msg_len = cpu_to_le32(sizeof *u.get + in_len);
	u.get->oid = oid;
	u.get->len = cpu_to_le32(in_len);
	u.get->offset = cpu_to_le32(20);

	retval = rndis_command(dev, u.header, CONTROL_BUFFER_SIZE);
	if (unlikely(retval < 0)) {
		dev_err(&intf->dev, "RNDIS_MSG_QUERY(0x%08x) failed, %d\n",
				oid, retval);
		return retval;
	}

	off = le32_to_cpu(u.get_c->offset);
	len = le32_to_cpu(u.get_c->len);
	if (unlikely((8 + off + len) > CONTROL_BUFFER_SIZE))
		goto response_error;

	if (*reply_len != -1 && len != *reply_len)
		goto response_error;

	*reply = (unsigned char *) &u.get_c->request_id + off;
	*reply_len = len;

	return retval;

response_error:
	dev_err(&intf->dev, "RNDIS_MSG_QUERY(0x%08x) "
			"invalid response - off %d len %d\n",
		oid, off, len);
	return -EDOM;
}