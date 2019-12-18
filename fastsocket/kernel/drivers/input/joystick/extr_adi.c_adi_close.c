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
struct adi_port {int /*<<< orphan*/  gameport; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_stop_polling (int /*<<< orphan*/ ) ; 
 struct adi_port* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void adi_close(struct input_dev *dev)
{
	struct adi_port *port = input_get_drvdata(dev);

	gameport_stop_polling(port->gameport);
}