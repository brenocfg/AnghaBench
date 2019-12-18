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
struct zcrypt_device {char* type_string; int short_crt; int online; void* ops; int /*<<< orphan*/  reply; struct ap_device* ap_dev; int /*<<< orphan*/  speed_rating; void* max_exp_bit_length; void* max_mod_size; int /*<<< orphan*/  min_mod_size; int /*<<< orphan*/  user_space_type; } ;
struct ap_device {int device_type; struct zcrypt_device* private; int /*<<< orphan*/ * reply; int /*<<< orphan*/  functions; } ;

/* Variables and functions */
#define  AP_DEVICE_TYPE_CEX4 128 
 int /*<<< orphan*/  AP_FUNC_ACCEL ; 
 int /*<<< orphan*/  AP_FUNC_COPRO ; 
 int /*<<< orphan*/  AP_FUNC_CRT4K ; 
 int /*<<< orphan*/  AP_FUNC_MEX4K ; 
 int /*<<< orphan*/  CEX4A_MAX_MESSAGE_SIZE ; 
 void* CEX4A_MAX_MOD_SIZE_2K ; 
 void* CEX4A_MAX_MOD_SIZE_4K ; 
 int /*<<< orphan*/  CEX4A_MIN_MOD_SIZE ; 
 int /*<<< orphan*/  CEX4A_SPEED_RATING ; 
 int /*<<< orphan*/  CEX4C_MAX_MESSAGE_SIZE ; 
 void* CEX4C_MAX_MOD_SIZE ; 
 int /*<<< orphan*/  CEX4C_MIN_MOD_SIZE ; 
 int /*<<< orphan*/  CEX4C_SPEED_RATING ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MSGTYPE06_NAME ; 
 int /*<<< orphan*/  MSGTYPE06_VARIANT_DEFAULT ; 
 int /*<<< orphan*/  MSGTYPE50_NAME ; 
 int /*<<< orphan*/  MSGTYPE50_VARIANT_DEFAULT ; 
 int /*<<< orphan*/  ZCRYPT_CEX3A ; 
 int /*<<< orphan*/  ZCRYPT_CEX3C ; 
 int /*<<< orphan*/  ap_test_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zcrypt_device* zcrypt_device_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_device_free (struct zcrypt_device*) ; 
 int zcrypt_device_register (struct zcrypt_device*) ; 
 int /*<<< orphan*/  zcrypt_msgtype_release (void*) ; 
 void* zcrypt_msgtype_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zcrypt_cex4_probe(struct ap_device *ap_dev)
{
	struct zcrypt_device *zdev = NULL;
	int rc = 0;

	switch (ap_dev->device_type) {
	case AP_DEVICE_TYPE_CEX4:
		if (ap_test_bit(&ap_dev->functions, AP_FUNC_ACCEL)) {
			zdev = zcrypt_device_alloc(CEX4A_MAX_MESSAGE_SIZE);
			if (!zdev)
				return -ENOMEM;
			zdev->type_string = "CEX4A";
			zdev->user_space_type = ZCRYPT_CEX3A;
			zdev->min_mod_size = CEX4A_MIN_MOD_SIZE;
			if (ap_test_bit(&ap_dev->functions, AP_FUNC_MEX4K) &&
			    ap_test_bit(&ap_dev->functions, AP_FUNC_CRT4K)) {
				zdev->max_mod_size =
					CEX4A_MAX_MOD_SIZE_4K;
				zdev->max_exp_bit_length =
					CEX4A_MAX_MOD_SIZE_4K;
			} else {
				zdev->max_mod_size =
					CEX4A_MAX_MOD_SIZE_2K;
				zdev->max_exp_bit_length =
					CEX4A_MAX_MOD_SIZE_2K;
			}
			zdev->short_crt = 1;
			zdev->speed_rating = CEX4A_SPEED_RATING;
			zdev->ops = zcrypt_msgtype_request(MSGTYPE50_NAME,
							   MSGTYPE50_VARIANT_DEFAULT);
		} else if (ap_test_bit(&ap_dev->functions, AP_FUNC_COPRO)) {
			zdev = zcrypt_device_alloc(CEX4C_MAX_MESSAGE_SIZE);
			if (!zdev)
				return -ENOMEM;
			zdev->type_string = "CEX4C";
			zdev->user_space_type = ZCRYPT_CEX3C;
			zdev->min_mod_size = CEX4C_MIN_MOD_SIZE;
			zdev->max_mod_size = CEX4C_MAX_MOD_SIZE;
			zdev->max_exp_bit_length = CEX4C_MAX_MOD_SIZE;
			zdev->short_crt = 0;
			zdev->speed_rating = CEX4C_SPEED_RATING;
			zdev->ops = zcrypt_msgtype_request(MSGTYPE06_NAME,
							   MSGTYPE06_VARIANT_DEFAULT);
		}
		break;
	}
	if (!zdev)
		return -ENODEV;
	zdev->ap_dev = ap_dev;
	zdev->online = 1;
	ap_dev->reply = &zdev->reply;
	ap_dev->private = zdev;
	rc = zcrypt_device_register(zdev);
	if (rc) {
		zcrypt_msgtype_release(zdev->ops);
		ap_dev->private = NULL;
		zcrypt_device_free(zdev);
	}
	return rc;
}