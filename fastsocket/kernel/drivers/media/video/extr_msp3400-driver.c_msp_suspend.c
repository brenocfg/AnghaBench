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
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  msp_debug ; 
 int /*<<< orphan*/  msp_reset (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*) ; 

__attribute__((used)) static int msp_suspend(struct i2c_client *client, pm_message_t state)
{
	v4l_dbg(1, msp_debug, client, "suspend\n");
	msp_reset(client);
	return 0;
}