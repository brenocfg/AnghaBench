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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIL164_CONTROL0 ; 
 int /*<<< orphan*/  SIL164_CONTROL0_POWER_ON ; 
 int /*<<< orphan*/  sil164_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sil164_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sil164_set_power_state(struct i2c_client *client, bool on)
{
	uint8_t control0 = sil164_read(client, SIL164_CONTROL0);

	if (on)
		control0 |= SIL164_CONTROL0_POWER_ON;
	else
		control0 &= ~SIL164_CONTROL0_POWER_ON;

	sil164_write(client, SIL164_CONTROL0, control0);
}