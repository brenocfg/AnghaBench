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
struct tuner {int /*<<< orphan*/  type; int /*<<< orphan*/  standby; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  set_mode_freq (struct i2c_client*,struct tuner*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tuner* to_tuner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuner_dbg (char*) ; 

__attribute__((used)) static int tuner_resume(struct i2c_client *c)
{
	struct tuner *t = to_tuner(i2c_get_clientdata(c));

	tuner_dbg("resume\n");

	if (!t->standby)
		set_mode_freq(c, t, t->type, 0);

	return 0;
}