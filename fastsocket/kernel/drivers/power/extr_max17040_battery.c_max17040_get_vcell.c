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
struct max17040_chip {int vcell; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17040_VCELL_LSB ; 
 int /*<<< orphan*/  MAX17040_VCELL_MSB ; 
 struct max17040_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int max17040_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max17040_get_vcell(struct i2c_client *client)
{
	struct max17040_chip *chip = i2c_get_clientdata(client);
	u8 msb;
	u8 lsb;

	msb = max17040_read_reg(client, MAX17040_VCELL_MSB);
	lsb = max17040_read_reg(client, MAX17040_VCELL_LSB);

	chip->vcell = (msb << 4) + (lsb >> 4);
}