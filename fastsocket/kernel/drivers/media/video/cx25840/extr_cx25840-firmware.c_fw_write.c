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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*) ; 

__attribute__((used)) static int fw_write(struct i2c_client *client, const u8 *data, int size)
{
	if (i2c_master_send(client, data, size) < size) {
		v4l_err(client, "firmware load i2c failure\n");
		return -ENOSYS;
	}

	return 0;
}