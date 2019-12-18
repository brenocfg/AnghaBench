#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nouveau_timer {int (* read ) (struct nouveau_timer*) ;} ;
struct nouveau_therm_priv {TYPE_2__* fan; } ;
struct nouveau_therm {int dummy; } ;
struct nouveau_gpio {int (* get ) (struct nouveau_gpio*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ func; int /*<<< orphan*/  line; } ;
struct TYPE_4__ {TYPE_1__ tach; } ;

/* Variables and functions */
 scalar_t__ DCB_GPIO_UNUSED ; 
 int ENODEV ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct nouveau_gpio* nouveau_gpio (struct nouveau_therm*) ; 
 struct nouveau_timer* nouveau_timer (struct nouveau_therm*) ; 
 int stub1 (struct nouveau_timer*) ; 
 int stub2 (struct nouveau_gpio*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub3 (struct nouveau_timer*) ; 
 int stub4 (struct nouveau_gpio*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub5 (struct nouveau_timer*) ; 
 int stub6 (struct nouveau_timer*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int
nouveau_therm_fan_sense(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *priv = (void *)therm;
	struct nouveau_timer *ptimer = nouveau_timer(therm);
	struct nouveau_gpio *gpio = nouveau_gpio(therm);
	u32 cycles, cur, prev;
	u64 start, end, tach;

	if (priv->fan->tach.func == DCB_GPIO_UNUSED)
		return -ENODEV;

	/* Time a complete rotation and extrapolate to RPM:
	 * When the fan spins, it changes the value of GPIO FAN_SENSE.
	 * We get 4 changes (0 -> 1 -> 0 -> 1) per complete rotation.
	 */
	start = ptimer->read(ptimer);
	prev = gpio->get(gpio, 0, priv->fan->tach.func, priv->fan->tach.line);
	cycles = 0;
	do {
		usleep_range(500, 1000); /* supports 0 < rpm < 7500 */

		cur = gpio->get(gpio, 0, priv->fan->tach.func, priv->fan->tach.line);
		if (prev != cur) {
			if (!start)
				start = ptimer->read(ptimer);
			cycles++;
			prev = cur;
		}
	} while (cycles < 5 && ptimer->read(ptimer) - start < 250000000);
	end = ptimer->read(ptimer);

	if (cycles == 5) {
		tach = (u64)60000000000ULL;
		do_div(tach, (end - start));
		return tach;
	} else
		return 0;
}