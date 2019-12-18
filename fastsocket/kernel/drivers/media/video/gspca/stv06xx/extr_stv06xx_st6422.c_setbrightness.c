#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st6422_settings {TYPE_1__* ctrls; } ;
struct sd {struct st6422_settings* sensor_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 size_t BRIGHTNESS ; 
 int stv06xx_write_bridge (struct sd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setbrightness(struct sd *sd)
{
	struct st6422_settings *sensor_settings = sd->sensor_priv;

	/* val goes from 0 -> 31 */
	return stv06xx_write_bridge(sd, 0x1432,
			sensor_settings->ctrls[BRIGHTNESS].val);
}