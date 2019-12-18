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
typedef  int u8 ;
struct w9968cf_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ w9968cf_write_sb (struct w9968cf_device*,int) ; 

__attribute__((used)) static int w9968cf_smbus_write_byte(struct w9968cf_device* cam, u8 v)
{
	u8 bit;
	int err = 0, sda;

	for (bit = 0 ; bit < 8 ; bit++) {
		sda = (v & 0x80) ? 2 : 0;
		v <<= 1;
		/* SDE=1, SDA=sda, SCL=0 */
		err += w9968cf_write_sb(cam, 0x10 | sda);
		/* SDE=1, SDA=sda, SCL=1 */
		err += w9968cf_write_sb(cam, 0x11 | sda);
		/* SDE=1, SDA=sda, SCL=0 */
		err += w9968cf_write_sb(cam, 0x10 | sda);
	}

	return err;
}