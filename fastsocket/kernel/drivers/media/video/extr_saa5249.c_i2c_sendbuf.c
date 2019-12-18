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
struct saa5249_device {int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_master_send (struct i2c_client*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_sendbuf(struct saa5249_device *t, int reg, int count, u8 *data)
{
	struct i2c_client *client = v4l2_get_subdevdata(&t->sd);
	char buf[64];

	buf[0] = reg;
	memcpy(buf+1, data, count);

	if (i2c_master_send(client, buf, count + 1) == count + 1)
		return 0;
	return -1;
}