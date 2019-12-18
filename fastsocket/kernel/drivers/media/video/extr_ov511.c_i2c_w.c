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
struct usb_ov511 {scalar_t__ bclass; int /*<<< orphan*/  i2c_lock; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov511_i2c_write_internal (struct usb_ov511*,unsigned char,unsigned char) ; 
 int ov518_i2c_write_internal (struct usb_ov511*,unsigned char,unsigned char) ; 

__attribute__((used)) static int
i2c_w(struct usb_ov511 *ov, unsigned char reg, unsigned char value)
{
	int rc;

	mutex_lock(&ov->i2c_lock);

	if (ov->bclass == BCL_OV518)
		rc = ov518_i2c_write_internal(ov, reg, value);
	else
		rc = ov511_i2c_write_internal(ov, reg, value);

	mutex_unlock(&ov->i2c_lock);

	return rc;
}