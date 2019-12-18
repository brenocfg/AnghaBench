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
 int w9968cf_read_sb (struct w9968cf_device*) ; 
 scalar_t__ w9968cf_write_sb (struct w9968cf_device*,int) ; 

__attribute__((used)) static int w9968cf_smbus_read_byte(struct w9968cf_device* cam, u8* v)
{
	u8 bit;
	int err = 0;

	*v = 0;
	for (bit = 0 ; bit < 8 ; bit++) {
		*v <<= 1;
		err += w9968cf_write_sb(cam, 0x0013);
		*v |= (w9968cf_read_sb(cam) & 0x0008) ? 1 : 0;
		err += w9968cf_write_sb(cam, 0x0012);
	}

	return err;
}