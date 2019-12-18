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
struct gameport_driver {int dummy; } ;
struct gameport {scalar_t__ (* open ) (struct gameport*,int) ;} ;

/* Variables and functions */
 int GAMEPORT_MODE_RAW ; 
 int /*<<< orphan*/  gameport_set_drv (struct gameport*,struct gameport_driver*) ; 
 scalar_t__ stub1 (struct gameport*,int) ; 

int gameport_open(struct gameport *gameport, struct gameport_driver *drv, int mode)
{
	if (gameport->open) {
		if (gameport->open(gameport, mode)) {
			return -1;
		}
	} else {
		if (mode != GAMEPORT_MODE_RAW)
			return -1;
	}

	gameport_set_drv(gameport, drv);
	return 0;
}