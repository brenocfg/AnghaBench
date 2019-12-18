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
struct pcf8563 {scalar_t__ rtc; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct pcf8563* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct pcf8563*) ; 
 int /*<<< orphan*/  rtc_device_unregister (scalar_t__) ; 

__attribute__((used)) static int pcf8563_remove(struct i2c_client *client)
{
	struct pcf8563 *pcf8563 = i2c_get_clientdata(client);

	if (pcf8563->rtc)
		rtc_device_unregister(pcf8563->rtc);

	kfree(pcf8563);

	return 0;
}