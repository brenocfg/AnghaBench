#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct zcrypt_device {int /*<<< orphan*/  online; } ;
struct TYPE_6__ {int cprb_ver_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  apfs; } ;
struct TYPE_4__ {int /*<<< orphan*/  reply_code; } ;
struct type86x_reply {TYPE_3__ cprbx; TYPE_2__ fmt2; TYPE_1__ hdr; } ;
struct ica_xcRB {int status; } ;
struct ap_message {struct type86x_reply* message; } ;

/* Variables and functions */
 int EAGAIN ; 
#define  TYPE82_RSP_CODE 130 
#define  TYPE86_RSP_CODE 129 
#define  TYPE88_RSP_CODE 128 
 int convert_error (struct zcrypt_device*,struct ap_message*) ; 
 int convert_type86_xcrb (struct zcrypt_device*,struct ap_message*,struct ica_xcRB*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int convert_response_xcrb(struct zcrypt_device *zdev,
			    struct ap_message *reply,
			    struct ica_xcRB *xcRB)
{
	struct type86x_reply *msg = reply->message;

	/* Response type byte is the second byte in the response. */
	switch (((unsigned char *) reply->message)[1]) {
	case TYPE82_RSP_CODE:
	case TYPE88_RSP_CODE:
		xcRB->status = 0x0008044DL; /* HDD_InvalidParm */
		return convert_error(zdev, reply);
	case TYPE86_RSP_CODE:
		if (msg->hdr.reply_code) {
			memcpy(&(xcRB->status), msg->fmt2.apfs, sizeof(u32));
			return convert_error(zdev, reply);
		}
		if (msg->cprbx.cprb_ver_id == 0x02)
			return convert_type86_xcrb(zdev, reply, xcRB);
		/* Fall through, no break, incorrect cprb version is an unknown
		 * response */
	default: /* Unknown response type, this should NEVER EVER happen */
		xcRB->status = 0x0008044DL; /* HDD_InvalidParm */
		zdev->online = 0;
		return -EAGAIN;	/* repeat the request on a different device. */
	}
}