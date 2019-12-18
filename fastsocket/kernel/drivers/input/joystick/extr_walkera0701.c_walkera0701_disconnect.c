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
struct walkera_dev {int /*<<< orphan*/  parport; int /*<<< orphan*/  pardevice; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_put_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void walkera0701_disconnect(struct walkera_dev *w)
{
	hrtimer_cancel(&w->timer);
	input_unregister_device(w->input_dev);
	parport_release(w->pardevice);
	parport_unregister_device(w->pardevice);
	parport_put_port(w->parport);
}