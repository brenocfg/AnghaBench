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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int hwrng_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zcrypt_rng_buffer ; 
 scalar_t__ zcrypt_rng_buffer_index ; 
 int /*<<< orphan*/  zcrypt_rng_dev ; 
 int zcrypt_rng_device_count ; 
 int /*<<< orphan*/  zcrypt_rng_mutex ; 

__attribute__((used)) static int zcrypt_rng_device_add(void)
{
	int rc = 0;

	mutex_lock(&zcrypt_rng_mutex);
	if (zcrypt_rng_device_count == 0) {
		zcrypt_rng_buffer = (u32 *) get_zeroed_page(GFP_KERNEL);
		if (!zcrypt_rng_buffer) {
			rc = -ENOMEM;
			goto out;
		}
		zcrypt_rng_buffer_index = 0;
		rc = hwrng_register(&zcrypt_rng_dev);
		if (rc)
			goto out_free;
		zcrypt_rng_device_count = 1;
	} else
		zcrypt_rng_device_count++;
	mutex_unlock(&zcrypt_rng_mutex);
	return 0;

out_free:
	free_page((unsigned long) zcrypt_rng_buffer);
out:
	mutex_unlock(&zcrypt_rng_mutex);
	return rc;
}