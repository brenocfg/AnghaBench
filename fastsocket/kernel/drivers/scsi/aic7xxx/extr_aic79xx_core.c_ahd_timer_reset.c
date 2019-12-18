#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct ahd_softc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * function; scalar_t__ expires; scalar_t__ data; } ;
typedef  TYPE_1__ ahd_timer_t ;
typedef  int /*<<< orphan*/  ahd_linux_callback_t ;
typedef  int /*<<< orphan*/  ahd_callback_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void
ahd_timer_reset(ahd_timer_t *timer, int usec, ahd_callback_t *func, void *arg)
{
	struct ahd_softc *ahd;

	ahd = (struct ahd_softc *)arg;
	del_timer(timer);
	timer->data = (u_long)arg;
	timer->expires = jiffies + (usec * HZ)/1000000;
	timer->function = (ahd_linux_callback_t*)func;
	add_timer(timer);
}