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
struct sg_io_v4 {char guard; int protocol; scalar_t__ dout_xfer_len; int /*<<< orphan*/  subprotocol; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
#define  BSG_PROTOCOL_SCSI 130 
#define  BSG_SUB_PROTOCOL_SCSI_CMD 129 
#define  BSG_SUB_PROTOCOL_SCSI_TRANSPORT 128 
 int EINVAL ; 
 int READ ; 
 int WRITE ; 

__attribute__((used)) static int
bsg_validate_sgv4_hdr(struct request_queue *q, struct sg_io_v4 *hdr, int *rw)
{
	int ret = 0;

	if (hdr->guard != 'Q')
		return -EINVAL;

	switch (hdr->protocol) {
	case BSG_PROTOCOL_SCSI:
		switch (hdr->subprotocol) {
		case BSG_SUB_PROTOCOL_SCSI_CMD:
		case BSG_SUB_PROTOCOL_SCSI_TRANSPORT:
			break;
		default:
			ret = -EINVAL;
		}
		break;
	default:
		ret = -EINVAL;
	}

	*rw = hdr->dout_xfer_len ? WRITE : READ;
	return ret;
}