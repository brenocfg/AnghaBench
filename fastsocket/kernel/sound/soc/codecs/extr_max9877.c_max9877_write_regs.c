#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX9877_INPUT_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* i2c ; 
 int i2c_master_send (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * max9877_regs ; 

__attribute__((used)) static void max9877_write_regs(void)
{
	unsigned int i;
	u8 data[6];

	data[0] = MAX9877_INPUT_MODE;
	for (i = 0; i < ARRAY_SIZE(max9877_regs); i++)
		data[i + 1] = max9877_regs[i];

	if (i2c_master_send(i2c, data, 6) != 6)
		dev_err(&i2c->dev, "i2c write failed\n");
}