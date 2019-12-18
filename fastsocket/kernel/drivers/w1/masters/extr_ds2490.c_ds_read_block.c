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
struct ds_status {int dummy; } ;
struct ds_device {int dummy; } ;

/* Variables and functions */
 int COMM_BLOCK_IO ; 
 int COMM_IM ; 
 int E2BIG ; 
 int ds_recv_data (struct ds_device*,int /*<<< orphan*/ *,int) ; 
 int ds_send_control (struct ds_device*,int,int) ; 
 int ds_send_data (struct ds_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ds_wait_status (struct ds_device*,struct ds_status*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int ds_read_block(struct ds_device *dev, u8 *buf, int len)
{
	struct ds_status st;
	int err;

	if (len > 64*1024)
		return -E2BIG;

	memset(buf, 0xFF, len);

	err = ds_send_data(dev, buf, len);
	if (err < 0)
		return err;

	err = ds_send_control(dev, COMM_BLOCK_IO | COMM_IM, len);
	if (err)
		return err;

	ds_wait_status(dev, &st);

	memset(buf, 0x00, len);
	err = ds_recv_data(dev, buf, len);

	return err;
}