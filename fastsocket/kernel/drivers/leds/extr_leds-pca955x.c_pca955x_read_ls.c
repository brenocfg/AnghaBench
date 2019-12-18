#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pca955x_led {TYPE_1__* chipdef; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 struct pca955x_led* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 
 scalar_t__ pca95xx_num_input_regs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 pca955x_read_ls(struct i2c_client *client, int n)
{
	struct pca955x_led *pca955x = i2c_get_clientdata(client);

	return (u8) i2c_smbus_read_byte_data(client,
		pca95xx_num_input_regs(pca955x->chipdef->bits) + 4 + n);
}