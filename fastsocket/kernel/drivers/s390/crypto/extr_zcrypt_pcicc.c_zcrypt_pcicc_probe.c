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
struct zcrypt_device {int online; char* type_string; int /*<<< orphan*/  reply; void* max_exp_bit_length; int /*<<< orphan*/  speed_rating; void* max_mod_size; int /*<<< orphan*/  min_mod_size; int /*<<< orphan*/  user_space_type; int /*<<< orphan*/ * ops; struct ap_device* ap_dev; } ;
struct ap_device {struct zcrypt_device* private; int /*<<< orphan*/ * reply; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* PCICC_MAX_MOD_SIZE ; 
 int /*<<< orphan*/  PCICC_MAX_RESPONSE_SIZE ; 
 int /*<<< orphan*/  PCICC_MIN_MOD_SIZE ; 
 int /*<<< orphan*/  PCICC_SPEED_RATING ; 
 int /*<<< orphan*/  ZCRYPT_PCICC ; 
 struct zcrypt_device* zcrypt_device_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_device_free (struct zcrypt_device*) ; 
 int zcrypt_device_register (struct zcrypt_device*) ; 
 int /*<<< orphan*/  zcrypt_pcicc_ops ; 

__attribute__((used)) static int zcrypt_pcicc_probe(struct ap_device *ap_dev)
{
	struct zcrypt_device *zdev;
	int rc;

	zdev = zcrypt_device_alloc(PCICC_MAX_RESPONSE_SIZE);
	if (!zdev)
		return -ENOMEM;
	zdev->ap_dev = ap_dev;
	zdev->ops = &zcrypt_pcicc_ops;
	zdev->online = 1;
	zdev->user_space_type = ZCRYPT_PCICC;
	zdev->type_string = "PCICC";
	zdev->min_mod_size = PCICC_MIN_MOD_SIZE;
	zdev->max_mod_size = PCICC_MAX_MOD_SIZE;
	zdev->speed_rating = PCICC_SPEED_RATING;
	zdev->max_exp_bit_length = PCICC_MAX_MOD_SIZE;
	ap_dev->reply = &zdev->reply;
	ap_dev->private = zdev;
	rc = zcrypt_device_register(zdev);
	if (rc)
		goto out_free;
	return 0;

 out_free:
	ap_dev->private = NULL;
	zcrypt_device_free(zdev);
	return rc;
}