#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; int* gpio; int /*<<< orphan*/ * gpio_pol; } ;
struct zoran {TYPE_1__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO (struct zoran*,int,int) ; 
#define  LML33 129 
#define  LML33R10 128 
 size_t ZR_GPIO_VID_DIR ; 
 int /*<<< orphan*/  lml33dpath ; 

__attribute__((used)) static void
set_videobus_dir (struct zoran *zr,
		  int           val)
{
	switch (zr->card.type) {
	case LML33:
	case LML33R10:
		if (lml33dpath == 0)
			GPIO(zr, 5, val);
		else
			GPIO(zr, 5, 1);
		break;
	default:
		GPIO(zr, zr->card.gpio[ZR_GPIO_VID_DIR],
		     zr->card.gpio_pol[ZR_GPIO_VID_DIR] ? !val : val);
		break;
	}
}