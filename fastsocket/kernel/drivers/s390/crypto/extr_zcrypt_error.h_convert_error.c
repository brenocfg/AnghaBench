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
struct zcrypt_device {int /*<<< orphan*/  online; TYPE_1__* ap_dev; } ;
struct error_hdr {int reply_code; } ;
struct ap_message {struct error_hdr* message; } ;
struct TYPE_2__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_ERR ; 
 int EAGAIN ; 
 int EINVAL ; 
#define  REP82_ERROR_EVEN_MOD_IN_OPND 134 
#define  REP82_ERROR_MACHINE_FAILURE 133 
#define  REP82_ERROR_MESSAGE_TYPE 132 
#define  REP82_ERROR_OPERAND_INVALID 131 
#define  REP82_ERROR_OPERAND_SIZE 130 
#define  REP82_ERROR_TRANSPORT_FAIL 129 
#define  REP88_ERROR_MESSAGE_MALFORMD 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ZCRYPT_DBF_DEV (int /*<<< orphan*/ ,struct zcrypt_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zcrypt_rescan_req ; 

__attribute__((used)) static inline int convert_error(struct zcrypt_device *zdev,
				struct ap_message *reply)
{
	struct error_hdr *ehdr = reply->message;

	switch (ehdr->reply_code) {
	case REP82_ERROR_OPERAND_INVALID:
	case REP82_ERROR_OPERAND_SIZE:
	case REP82_ERROR_EVEN_MOD_IN_OPND:
	case REP88_ERROR_MESSAGE_MALFORMD:
	//   REP88_ERROR_INVALID_KEY		// '82' CEX2A
	//   REP88_ERROR_OPERAND		// '84' CEX2A
	//   REP88_ERROR_OPERAND_EVEN_MOD	// '85' CEX2A
		/* Invalid input data. */
		return -EINVAL;
	case REP82_ERROR_MESSAGE_TYPE:
	//   REP88_ERROR_MESSAGE_TYPE		// '20' CEX2A
		/*
		 * To sent a message of the wrong type is a bug in the
		 * device driver. Warn about it, disable the device
		 * and then repeat the request.
		 */
		WARN_ON(1);
		atomic_set(&zcrypt_rescan_req, 1);
		zdev->online = 0;
		ZCRYPT_DBF_DEV(DBF_ERR, zdev, "dev%04xo%drc%d",
			       zdev->ap_dev->qid,
			       zdev->online, ehdr->reply_code);
		return -EAGAIN;
	case REP82_ERROR_TRANSPORT_FAIL:
	case REP82_ERROR_MACHINE_FAILURE:
	//   REP88_ERROR_MODULE_FAILURE		// '10' CEX2A
		/* If a card fails disable it and repeat the request. */
		atomic_set(&zcrypt_rescan_req, 1);
		zdev->online = 0;
		ZCRYPT_DBF_DEV(DBF_ERR, zdev, "dev%04xo%drc%d",
			       zdev->ap_dev->qid,
			       zdev->online, ehdr->reply_code);
		return -EAGAIN;
	default:
		zdev->online = 0;
		ZCRYPT_DBF_DEV(DBF_ERR, zdev, "dev%04xo%drc%d",
			       zdev->ap_dev->qid,
			       zdev->online, ehdr->reply_code);
		return -EAGAIN;	/* repeat the request on a different device. */
	}
}