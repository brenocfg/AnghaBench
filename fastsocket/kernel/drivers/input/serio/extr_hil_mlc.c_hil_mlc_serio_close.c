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
struct serio {int /*<<< orphan*/ * drv; struct hil_mlc_serio_map* port_data; } ;
struct hil_mlc_serio_map {struct hil_mlc* mlc; } ;
struct hil_mlc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hil_mlc_serio_close(struct serio *serio)
{
	struct hil_mlc_serio_map *map;
	struct hil_mlc *mlc;

	map = serio->port_data;
	BUG_ON(map == NULL);

	mlc = map->mlc;
	BUG_ON(mlc == NULL);

	serio_set_drvdata(serio, NULL);
	serio->drv = NULL;
	/* TODO wake up interruptable */
}