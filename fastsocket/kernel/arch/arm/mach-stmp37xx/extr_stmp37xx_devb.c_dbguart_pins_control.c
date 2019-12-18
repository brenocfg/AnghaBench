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

/* Variables and functions */
 int /*<<< orphan*/ * dbguart_pins ; 
 int /*<<< orphan*/  stmp3xxx_release_pin_group (int /*<<< orphan*/ *,char*) ; 
 int stmp3xxx_request_pin_group (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int dbguart_pins_control(int id, int request)
{
	int r = 0;

	if (request)
		r = stmp3xxx_request_pin_group(&dbguart_pins[id], "debug uart");
	else
		stmp3xxx_release_pin_group(&dbguart_pins[id], "debug uart");
	return r;
}