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
struct et61x251_sensor {int dummy; } ;
struct et61x251_device {int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct et61x251_sensor const*,int) ; 

void
et61x251_attach_sensor(struct et61x251_device* cam,
		       const struct et61x251_sensor* sensor)
{
	memcpy(&cam->sensor, sensor, sizeof(struct et61x251_sensor));
}