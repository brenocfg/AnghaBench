#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_device {int /*<<< orphan*/  online; } ;
struct TYPE_4__ {int cprb_ver_id; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/  reply_code; } ;
struct type86x_reply {TYPE_2__ cprbx; TYPE_1__ hdr; } ;
struct ap_message {struct type86x_reply* message; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
#define  TYPE82_RSP_CODE 130 
#define  TYPE86_RSP_CODE 129 
#define  TYPE88_RSP_CODE 128 
 int convert_type86_rng (struct zcrypt_device*,struct ap_message*,char*) ; 

__attribute__((used)) static int convert_response_rng(struct zcrypt_device *zdev,
				 struct ap_message *reply,
				 char *data)
{
	struct type86x_reply *msg = reply->message;

	switch (msg->hdr.type) {
	case TYPE82_RSP_CODE:
	case TYPE88_RSP_CODE:
		return -EINVAL;
	case TYPE86_RSP_CODE:
		if (msg->hdr.reply_code)
			return -EINVAL;
		if (msg->cprbx.cprb_ver_id == 0x02)
			return convert_type86_rng(zdev, reply, data);
		/* Fall through, no break, incorrect cprb version is an unknown
		 * response */
	default: /* Unknown response type, this should NEVER EVER happen */
		zdev->online = 0;
		return -EAGAIN;	/* repeat the request on a different device. */
	}
}