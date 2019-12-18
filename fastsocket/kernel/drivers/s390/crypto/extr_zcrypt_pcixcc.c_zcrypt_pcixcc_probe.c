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
struct zcrypt_device {int online; int user_space_type; char* type_string; void* ops; int /*<<< orphan*/  reply; void* max_exp_bit_length; void* max_mod_size; void* min_mod_size; int /*<<< orphan*/  speed_rating; struct ap_device* ap_dev; } ;
struct ap_device {int device_type; struct zcrypt_device* private; int /*<<< orphan*/ * reply; } ;

/* Variables and functions */
#define  AP_DEVICE_TYPE_CEX2C 130 
#define  AP_DEVICE_TYPE_CEX3C 129 
#define  AP_DEVICE_TYPE_PCIXCC 128 
 int /*<<< orphan*/  CEX2C_SPEED_RATING ; 
 void* CEX3C_MAX_MOD_SIZE ; 
 void* CEX3C_MIN_MOD_SIZE ; 
 int /*<<< orphan*/  CEX3C_SPEED_RATING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MSGTYPE06_NAME ; 
 int /*<<< orphan*/  MSGTYPE06_VARIANT_DEFAULT ; 
 int /*<<< orphan*/  MSGTYPE06_VARIANT_NORNG ; 
 void* PCIXCC_MAX_MOD_SIZE ; 
 int /*<<< orphan*/  PCIXCC_MAX_XCRB_MESSAGE_SIZE ; 
 int /*<<< orphan*/  PCIXCC_MCL2_SPEED_RATING ; 
 int /*<<< orphan*/  PCIXCC_MCL3_SPEED_RATING ; 
 void* PCIXCC_MIN_MOD_SIZE ; 
 void* PCIXCC_MIN_MOD_SIZE_OLD ; 
 int ZCRYPT_CEX2C ; 
 int ZCRYPT_CEX3C ; 
 int ZCRYPT_PCIXCC_MCL2 ; 
 struct zcrypt_device* zcrypt_device_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_device_free (struct zcrypt_device*) ; 
 int zcrypt_device_register (struct zcrypt_device*) ; 
 int /*<<< orphan*/  zcrypt_msgtype_release (void*) ; 
 void* zcrypt_msgtype_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zcrypt_pcixcc_mcl (struct ap_device*) ; 
 int zcrypt_pcixcc_rng_supported (struct ap_device*) ; 

__attribute__((used)) static int zcrypt_pcixcc_probe(struct ap_device *ap_dev)
{
	struct zcrypt_device *zdev;
	int rc = 0;

	zdev = zcrypt_device_alloc(PCIXCC_MAX_XCRB_MESSAGE_SIZE);
	if (!zdev)
		return -ENOMEM;
	zdev->ap_dev = ap_dev;
	zdev->online = 1;
	switch (ap_dev->device_type) {
	case AP_DEVICE_TYPE_PCIXCC:
		rc = zcrypt_pcixcc_mcl(ap_dev);
		if (rc < 0) {
			zcrypt_device_free(zdev);
			return rc;
		}
		zdev->user_space_type = rc;
		if (rc == ZCRYPT_PCIXCC_MCL2) {
			zdev->type_string = "PCIXCC_MCL2";
			zdev->speed_rating = PCIXCC_MCL2_SPEED_RATING;
			zdev->min_mod_size = PCIXCC_MIN_MOD_SIZE_OLD;
			zdev->max_mod_size = PCIXCC_MAX_MOD_SIZE;
			zdev->max_exp_bit_length = PCIXCC_MAX_MOD_SIZE;
		} else {
			zdev->type_string = "PCIXCC_MCL3";
			zdev->speed_rating = PCIXCC_MCL3_SPEED_RATING;
			zdev->min_mod_size = PCIXCC_MIN_MOD_SIZE;
			zdev->max_mod_size = PCIXCC_MAX_MOD_SIZE;
			zdev->max_exp_bit_length = PCIXCC_MAX_MOD_SIZE;
		}
		break;
	case AP_DEVICE_TYPE_CEX2C:
		zdev->user_space_type = ZCRYPT_CEX2C;
		zdev->type_string = "CEX2C";
		zdev->speed_rating = CEX2C_SPEED_RATING;
		zdev->min_mod_size = PCIXCC_MIN_MOD_SIZE;
		zdev->max_mod_size = PCIXCC_MAX_MOD_SIZE;
		zdev->max_exp_bit_length = PCIXCC_MAX_MOD_SIZE;
		break;
	case AP_DEVICE_TYPE_CEX3C:
		zdev->user_space_type = ZCRYPT_CEX3C;
		zdev->type_string = "CEX3C";
		zdev->speed_rating = CEX3C_SPEED_RATING;
		zdev->min_mod_size = CEX3C_MIN_MOD_SIZE;
		zdev->max_mod_size = CEX3C_MAX_MOD_SIZE;
		zdev->max_exp_bit_length = CEX3C_MAX_MOD_SIZE;
		break;
	default:
		goto out_free;
	}

	rc = zcrypt_pcixcc_rng_supported(ap_dev);
	if (rc < 0) {
		zcrypt_device_free(zdev);
		return rc;
	}
	if (rc)
		zdev->ops = zcrypt_msgtype_request(MSGTYPE06_NAME,
						   MSGTYPE06_VARIANT_DEFAULT);
	else
		zdev->ops = zcrypt_msgtype_request(MSGTYPE06_NAME,
						   MSGTYPE06_VARIANT_NORNG);
	ap_dev->reply = &zdev->reply;
	ap_dev->private = zdev;
	rc = zcrypt_device_register(zdev);
	if (rc)
		goto out_free;
	return 0;

 out_free:
	ap_dev->private = NULL;
	zcrypt_msgtype_release(zdev->ops);
	zcrypt_device_free(zdev);
	return rc;
}