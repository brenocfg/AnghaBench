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
struct zcrypt_device {scalar_t__ user_space_type; int /*<<< orphan*/  ap_dev; } ;
struct ica_rsa_modexpo_crt {int /*<<< orphan*/  outputdatalength; int /*<<< orphan*/  outputdata; } ;
struct completion {int dummy; } ;
struct ap_message {void* message; struct completion* private; scalar_t__ psmid; int /*<<< orphan*/  receive; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICACRT_msg_to_type50CRT_msg (struct zcrypt_device*,struct ap_message*,struct ica_rsa_modexpo_crt*) ; 
 int /*<<< orphan*/  MSGTYPE50_CRB2_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  MSGTYPE50_CRB3_MAX_MSG_SIZE ; 
 scalar_t__ ZCRYPT_CEX2A ; 
 int /*<<< orphan*/  ap_cancel_message (int /*<<< orphan*/ ,struct ap_message*) ; 
 int /*<<< orphan*/  ap_init_message (struct ap_message*) ; 
 int /*<<< orphan*/  ap_queue_message (int /*<<< orphan*/ ,struct ap_message*) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int convert_response (struct zcrypt_device*,struct ap_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_interruptible (struct completion*) ; 
 int /*<<< orphan*/  zcrypt_cex2a_receive ; 
 int /*<<< orphan*/  zcrypt_step ; 

__attribute__((used)) static long zcrypt_cex2a_modexpo_crt(struct zcrypt_device *zdev,
				     struct ica_rsa_modexpo_crt *crt)
{
	struct ap_message ap_msg;
	struct completion work;
	int rc;

	ap_init_message(&ap_msg);
	if (zdev->user_space_type == ZCRYPT_CEX2A)
		ap_msg.message = kmalloc(MSGTYPE50_CRB2_MAX_MSG_SIZE,
					 GFP_KERNEL);
	else
		ap_msg.message = kmalloc(MSGTYPE50_CRB3_MAX_MSG_SIZE,
					 GFP_KERNEL);
	if (!ap_msg.message)
		return -ENOMEM;
	ap_msg.receive = zcrypt_cex2a_receive;
	ap_msg.psmid = (((unsigned long long) current->pid) << 32) +
				atomic_inc_return(&zcrypt_step);
	ap_msg.private = &work;
	rc = ICACRT_msg_to_type50CRT_msg(zdev, &ap_msg, crt);
	if (rc)
		goto out_free;
	init_completion(&work);
	ap_queue_message(zdev->ap_dev, &ap_msg);
	rc = wait_for_completion_interruptible(&work);
	if (rc == 0)
		rc = convert_response(zdev, &ap_msg, crt->outputdata,
				      crt->outputdatalength);
	else
		/* Signal pending. */
		ap_cancel_message(zdev->ap_dev, &ap_msg);
out_free:
	kfree(ap_msg.message);
	return rc;
}