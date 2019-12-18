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
struct usb_device {int dummy; } ;
struct req_t {int cmd; int i2c_addr; int addr; int mbox; int addr_len; int data_len; int* data; } ;

/* Variables and functions */
 size_t ACK_HDR_LEN ; 
 int /*<<< orphan*/  AF9015_USB_TIMEOUT ; 
#define  BOOT 138 
 int BUF_LEN ; 
#define  COPY_FIRMWARE 137 
#define  DOWNLOAD_FIRMWARE 136 
 int EAGAIN ; 
 int EINVAL ; 
#define  GET_CONFIG 135 
#define  GET_IR_CODE 134 
#define  READ_I2C 133 
#define  READ_MEMORY 132 
 int READ_WRITE_I2C ; 
#define  RECONNECT_USB 131 
 size_t REQ_HDR_LEN ; 
#define  WRITE_I2C 130 
#define  WRITE_MEMORY 129 
#define  WRITE_VIRTUAL_MEMORY 128 
 int /*<<< orphan*/  af9015_usb_mutex ; 
 int /*<<< orphan*/  deb_xfer (char*) ; 
 int /*<<< orphan*/  debug_dump (int*,int,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  err (char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int af9015_rw_udev(struct usb_device *udev, struct req_t *req)
{
#define BUF_LEN 63
#define REQ_HDR_LEN 8 /* send header size */
#define ACK_HDR_LEN 2 /* rece header size */
	int act_len, ret;
	u8 buf[BUF_LEN];
	u8 write = 1;
	u8 msg_len = REQ_HDR_LEN;
	static u8 seq; /* packet sequence number */

	if (mutex_lock_interruptible(&af9015_usb_mutex) < 0)
		return -EAGAIN;

	buf[0] = req->cmd;
	buf[1] = seq++;
	buf[2] = req->i2c_addr;
	buf[3] = req->addr >> 8;
	buf[4] = req->addr & 0xff;
	buf[5] = req->mbox;
	buf[6] = req->addr_len;
	buf[7] = req->data_len;

	switch (req->cmd) {
	case GET_CONFIG:
	case READ_MEMORY:
	case RECONNECT_USB:
	case GET_IR_CODE:
		write = 0;
		break;
	case READ_I2C:
		write = 0;
		buf[2] |= 0x01; /* set I2C direction */
	case WRITE_I2C:
		buf[0] = READ_WRITE_I2C;
		break;
	case WRITE_MEMORY:
		if (((req->addr & 0xff00) == 0xff00) ||
		    ((req->addr & 0xff00) == 0xae00))
			buf[0] = WRITE_VIRTUAL_MEMORY;
	case WRITE_VIRTUAL_MEMORY:
	case COPY_FIRMWARE:
	case DOWNLOAD_FIRMWARE:
	case BOOT:
		break;
	default:
		err("unknown command:%d", req->cmd);
		ret = -1;
		goto error_unlock;
	}

	/* buffer overflow check */
	if ((write && (req->data_len > BUF_LEN - REQ_HDR_LEN)) ||
		(!write && (req->data_len > BUF_LEN - ACK_HDR_LEN))) {
		err("too much data; cmd:%d len:%d", req->cmd, req->data_len);
		ret = -EINVAL;
		goto error_unlock;
	}

	/* write requested */
	if (write) {
		memcpy(&buf[REQ_HDR_LEN], req->data, req->data_len);
		msg_len += req->data_len;
	}

	deb_xfer(">>> ");
	debug_dump(buf, msg_len, deb_xfer);

	/* send req */
	ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, 0x02), buf, msg_len,
		&act_len, AF9015_USB_TIMEOUT);
	if (ret)
		err("bulk message failed:%d (%d/%d)", ret, msg_len, act_len);
	else
		if (act_len != msg_len)
			ret = -1; /* all data is not send */
	if (ret)
		goto error_unlock;

	/* no ack for those packets */
	if (req->cmd == DOWNLOAD_FIRMWARE || req->cmd == RECONNECT_USB)
		goto exit_unlock;

	/* write receives seq + status = 2 bytes
	   read receives seq + status + data = 2 + N bytes */
	msg_len = ACK_HDR_LEN;
	if (!write)
		msg_len += req->data_len;

	ret = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, 0x81), buf, msg_len,
		&act_len, AF9015_USB_TIMEOUT);
	if (ret) {
		err("recv bulk message failed:%d", ret);
		ret = -1;
		goto error_unlock;
	}

	deb_xfer("<<< ");
	debug_dump(buf, act_len, deb_xfer);

	/* remote controller query status is 1 if remote code is not received */
	if (req->cmd == GET_IR_CODE && buf[1] == 1) {
		buf[1] = 0; /* clear command "error" status */
		memset(&buf[2], 0, req->data_len);
		buf[3] = 1; /* no remote code received mark */
	}

	/* check status */
	if (buf[1]) {
		err("command failed:%d", buf[1]);
		ret = -1;
		goto error_unlock;
	}

	/* read request, copy returned data to return buf */
	if (!write)
		memcpy(req->data, &buf[ACK_HDR_LEN], req->data_len);

error_unlock:
exit_unlock:
	mutex_unlock(&af9015_usb_mutex);

	return ret;
}