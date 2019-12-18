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
typedef  int /*<<< orphan*/  u8 ;
struct matrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MATROX_GET_DATA ; 
 int /*<<< orphan*/  matrox_w1_read_reg (struct matrox_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 matrox_w1_read_ddc_bit(void *data)
{
	u8 ret;
	struct matrox_device *dev = data;

	ret = matrox_w1_read_reg(dev, MATROX_GET_DATA);

	return ret;
}