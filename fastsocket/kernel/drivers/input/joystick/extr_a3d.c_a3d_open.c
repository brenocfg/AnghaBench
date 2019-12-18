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
struct input_dev {int dummy; } ;
struct a3d {int /*<<< orphan*/  gameport; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_start_polling (int /*<<< orphan*/ ) ; 
 struct a3d* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int a3d_open(struct input_dev *dev)
{
	struct a3d *a3d = input_get_drvdata(dev);

	gameport_start_polling(a3d->gameport);
	return 0;
}