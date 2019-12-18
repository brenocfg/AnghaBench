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
struct saa7164_i2c {scalar_t__ i2c_rc; int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ *,unsigned int,void*) ; 

void saa7164_call_i2c_clients(struct saa7164_i2c *bus, unsigned int cmd,
	void *arg)
{
	if (bus->i2c_rc != 0)
		return;

	i2c_clients_command(&bus->i2c_adap, cmd, arg);
}