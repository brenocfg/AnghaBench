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
typedef  size_t u8 ;
struct i2c_client {int dummy; } ;
struct bt856 {size_t* reg; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 size_t BT856_REG_OFFSET ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,size_t,size_t) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bt856_write(struct bt856 *encoder, u8 reg, u8 value)
{
	struct i2c_client *client = v4l2_get_subdevdata(&encoder->sd);

	encoder->reg[reg - BT856_REG_OFFSET] = value;
	return i2c_smbus_write_byte_data(client, reg, value);
}