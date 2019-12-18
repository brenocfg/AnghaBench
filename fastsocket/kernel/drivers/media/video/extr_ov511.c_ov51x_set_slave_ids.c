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
struct usb_ov511 {int /*<<< orphan*/  i2c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV511_RESET_NOREGS ; 
 int i2c_set_slave_internal (struct usb_ov511*,unsigned char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov51x_reset (struct usb_ov511*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ov51x_set_slave_ids(struct usb_ov511 *ov, unsigned char sid)
{
	int rc;

	mutex_lock(&ov->i2c_lock);

	rc = i2c_set_slave_internal(ov, sid);
	if (rc < 0)
		goto out;

	// FIXME: Is this actually necessary?
	rc = ov51x_reset(ov, OV511_RESET_NOREGS);
out:
	mutex_unlock(&ov->i2c_lock);
	return rc;
}