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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_master_recv (struct i2c_client*,int*,int) ; 

__attribute__((used)) static int i2c_read_le16(struct i2c_client *client)
{
	u8 buf[2];
	int status;

	status = i2c_master_recv(client, buf, 2);
	if (status < 0)
		return status;
	return (buf[1] << 8) | buf[0];
}