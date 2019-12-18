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
struct em28xx {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EM28XX_R43_AC97BUSY ; 
 int em28xx_read_reg (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_warn (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int em28xx_is_ac97_ready(struct em28xx *dev)
{
	int ret, i;

	/* Wait up to 50 ms for AC97 command to complete */
	for (i = 0; i < 10; i++, msleep(5)) {
		ret = em28xx_read_reg(dev, EM28XX_R43_AC97BUSY);
		if (ret < 0)
			return ret;

		if (!(ret & 0x01))
			return 0;
	}

	em28xx_warn("AC97 command still being executed: not handled properly!\n");
	return -EBUSY;
}