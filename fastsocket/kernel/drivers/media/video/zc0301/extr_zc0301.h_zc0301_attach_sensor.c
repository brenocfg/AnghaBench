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
struct zc0301_sensor {int dummy; } ;
struct zc0301_device {int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct zc0301_sensor*,int) ; 

void
zc0301_attach_sensor(struct zc0301_device* cam, struct zc0301_sensor* sensor)
{
	memcpy(&cam->sensor, sensor, sizeof(struct zc0301_sensor));
}