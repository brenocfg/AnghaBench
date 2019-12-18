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
struct wm8350 {int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_recv (int /*<<< orphan*/ ,void*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wm8350_i2c_read_device(struct wm8350 *wm8350, char reg,
				  int bytes, void *dest)
{
	int ret;

	ret = i2c_master_send(wm8350->i2c_client, &reg, 1);
	if (ret < 0)
		return ret;
	ret = i2c_master_recv(wm8350->i2c_client, dest, bytes);
	if (ret < 0)
		return ret;
	if (ret != bytes)
		return -EIO;
	return 0;
}