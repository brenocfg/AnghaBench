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
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int EN_CODEC ; 
 scalar_t__ VORTEX_CODEC_CHN ; 
 scalar_t__ VORTEX_CODEC_CTRL ; 
 scalar_t__ VORTEX_CODEC_EN ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void vortex_codec_init(vortex_t * vortex)
{
	int i;

	for (i = 0; i < 32; i++) {
		/* the windows driver writes -i, so we write -i */
		hwwrite(vortex->mmio, (VORTEX_CODEC_CHN + (i << 2)), -i);
		msleep(2);
	}
	if (0) {
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x8068);
		msleep(1);
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x00e8);
		msleep(1);
	} else {
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x00a8);
		msleep(2);
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x80a8);
		msleep(2);
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x80e8);
		msleep(2);
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x80a8);
		msleep(2);
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x00a8);
		msleep(2);
		hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0x00e8);
	}
	for (i = 0; i < 32; i++) {
		hwwrite(vortex->mmio, (VORTEX_CODEC_CHN + (i << 2)), -i);
		msleep(5);
	}
	hwwrite(vortex->mmio, VORTEX_CODEC_CTRL, 0xe8);
	msleep(1);
	/* Enable codec channels 0 and 1. */
	hwwrite(vortex->mmio, VORTEX_CODEC_EN,
		hwread(vortex->mmio, VORTEX_CODEC_EN) | EN_CODEC);
}