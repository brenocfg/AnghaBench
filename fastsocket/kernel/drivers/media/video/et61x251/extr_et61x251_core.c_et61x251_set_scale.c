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
struct et61x251_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PDBGG (char*,int) ; 
 int et61x251_read_reg (struct et61x251_device*,int) ; 
 scalar_t__ et61x251_write_reg (struct et61x251_device*,int,int) ; 

__attribute__((used)) static int et61x251_set_scale(struct et61x251_device* cam, u8 scale)
{
	int r = 0, err = 0;

	r = et61x251_read_reg(cam, 0x12);
	if (r < 0)
		err += r;

	if (scale == 1)
		err += et61x251_write_reg(cam, r & ~0x01, 0x12);
	else if (scale == 2)
		err += et61x251_write_reg(cam, r | 0x01, 0x12);

	if (err)
		return -EIO;

	PDBGG("Scaling factor: %u", scale);

	return 0;
}