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
struct interact {int /*<<< orphan*/  gameport; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_stop_polling (int /*<<< orphan*/ ) ; 
 struct interact* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void interact_close(struct input_dev *dev)
{
	struct interact *interact = input_get_drvdata(dev);

	gameport_stop_polling(interact->gameport);
}