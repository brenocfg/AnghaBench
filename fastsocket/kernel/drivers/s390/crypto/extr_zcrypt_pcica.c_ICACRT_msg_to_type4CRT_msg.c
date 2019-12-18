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
struct zcrypt_device {int dummy; } ;
struct TYPE_2__ {int msg_len; int /*<<< orphan*/  msg_fmt; void* request_code; void* msg_type_code; } ;
struct type4_scr {unsigned char* p; unsigned char* q; unsigned char* dp; unsigned char* dq; unsigned char* u; unsigned char* message; TYPE_1__ header; } ;
struct type4_lcr {unsigned char* p; unsigned char* q; unsigned char* dp; unsigned char* dq; unsigned char* u; unsigned char* message; TYPE_1__ header; } ;
struct ica_rsa_modexpo_crt {int inputdatalength; int /*<<< orphan*/  inputdata; int /*<<< orphan*/  u_mult_inv; int /*<<< orphan*/  bq_key; int /*<<< orphan*/  bp_key; int /*<<< orphan*/  nq_prime; int /*<<< orphan*/  np_prime; } ;
struct ap_message {int length; struct type4_scr* message; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  TYPE4_LCR_FMT ; 
 void* TYPE4_REQU_CODE ; 
 int /*<<< orphan*/  TYPE4_SCR_FMT ; 
 void* TYPE4_TYPE_CODE ; 
 scalar_t__ copy_from_user (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct type4_scr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ICACRT_msg_to_type4CRT_msg(struct zcrypt_device *zdev,
				      struct ap_message *ap_msg,
				      struct ica_rsa_modexpo_crt *crt)
{
	unsigned char *p, *q, *dp, *dq, *u, *inp;
	int mod_len, short_len, long_len;

	mod_len = crt->inputdatalength;
	short_len = mod_len / 2;
	long_len = mod_len / 2 + 8;

	if (mod_len <= 128) {
		struct type4_scr *scr = ap_msg->message;
		memset(scr, 0, sizeof(*scr));
		ap_msg->length = sizeof(*scr);
		scr->header.msg_type_code = TYPE4_TYPE_CODE;
		scr->header.request_code = TYPE4_REQU_CODE;
		scr->header.msg_fmt = TYPE4_SCR_FMT;
		scr->header.msg_len = sizeof(*scr);
		p = scr->p + sizeof(scr->p) - long_len;
		q = scr->q + sizeof(scr->q) - short_len;
		dp = scr->dp + sizeof(scr->dp) - long_len;
		dq = scr->dq + sizeof(scr->dq) - short_len;
		u = scr->u + sizeof(scr->u) - long_len;
		inp = scr->message + sizeof(scr->message) - mod_len;
	} else {
		struct type4_lcr *lcr = ap_msg->message;
		memset(lcr, 0, sizeof(*lcr));
		ap_msg->length = sizeof(*lcr);
		lcr->header.msg_type_code = TYPE4_TYPE_CODE;
		lcr->header.request_code = TYPE4_REQU_CODE;
		lcr->header.msg_fmt = TYPE4_LCR_FMT;
		lcr->header.msg_len = sizeof(*lcr);
		p = lcr->p + sizeof(lcr->p) - long_len;
		q = lcr->q + sizeof(lcr->q) - short_len;
		dp = lcr->dp + sizeof(lcr->dp) - long_len;
		dq = lcr->dq + sizeof(lcr->dq) - short_len;
		u = lcr->u + sizeof(lcr->u) - long_len;
		inp = lcr->message + sizeof(lcr->message) - mod_len;
	}

	if (copy_from_user(p, crt->np_prime, long_len) ||
	    copy_from_user(q, crt->nq_prime, short_len) ||
	    copy_from_user(dp, crt->bp_key, long_len) ||
	    copy_from_user(dq, crt->bq_key, short_len) ||
	    copy_from_user(u, crt->u_mult_inv, long_len) ||
	    copy_from_user(inp, crt->inputdata, mod_len))
		return -EFAULT;
	return 0;
}