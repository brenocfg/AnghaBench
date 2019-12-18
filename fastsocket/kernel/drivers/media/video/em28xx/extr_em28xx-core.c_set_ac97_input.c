#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct em28xx {int ctl_ainput; } ;
typedef  enum em28xx_amux { ____Placeholder_em28xx_amux } em28xx_amux ;
struct TYPE_3__ {int mux; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EM28XX_AMUX_VIDEO ; 
 int EM28XX_AMUX_VIDEO2 ; 
 int /*<<< orphan*/  em28xx_warn (char*,int /*<<< orphan*/ ) ; 
 int em28xx_write_ac97 (struct em28xx*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* inputs ; 

__attribute__((used)) static int set_ac97_input(struct em28xx *dev)
{
	int ret, i;
	enum em28xx_amux amux = dev->ctl_ainput;

	/* EM28XX_AMUX_VIDEO2 is a special case used to indicate that
	   em28xx should point to LINE IN, while AC97 should use VIDEO
	 */
	if (amux == EM28XX_AMUX_VIDEO2)
		amux = EM28XX_AMUX_VIDEO;

	/* Mute all entres but the one that were selected */
	for (i = 0; i < ARRAY_SIZE(inputs); i++) {
		if (amux == inputs[i].mux)
			ret = em28xx_write_ac97(dev, inputs[i].reg, 0x0808);
		else
			ret = em28xx_write_ac97(dev, inputs[i].reg, 0x8000);

		if (ret < 0)
			em28xx_warn("couldn't setup AC97 register %d\n",
				     inputs[i].reg);
	}
	return 0;
}