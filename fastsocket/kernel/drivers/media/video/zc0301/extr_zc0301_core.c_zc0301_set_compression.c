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
struct zc0301_device {int dummy; } ;
struct v4l2_jpegcompression {int quality; } ;

/* Variables and functions */
 int EIO ; 
 int zc0301_read_reg (struct zc0301_device*,int) ; 
 scalar_t__ zc0301_write_reg (struct zc0301_device*,int,int) ; 

__attribute__((used)) static int
zc0301_set_compression(struct zc0301_device* cam,
		       struct v4l2_jpegcompression* compression)
{
	int r, err = 0;

	if ((r = zc0301_read_reg(cam, 0x0008)) < 0)
		err += r;
	err += zc0301_write_reg(cam, 0x0008, r | 0x11 | compression->quality);

	return err ? -EIO : 0;
}