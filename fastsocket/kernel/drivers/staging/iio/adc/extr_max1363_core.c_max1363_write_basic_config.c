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
typedef  unsigned char u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max1363_write_basic_config(struct i2c_client *client,
				      unsigned char d1,
				      unsigned char d2)
{
	int ret;
	u8 *tx_buf = kmalloc(2 , GFP_KERNEL);
	if (!tx_buf)
		return -ENOMEM;
	tx_buf[0] = d1;
	tx_buf[1] = d2;

	ret = i2c_master_send(client, tx_buf, 2);
	kfree(tx_buf);
	return (ret > 0) ? 0 : ret;
}