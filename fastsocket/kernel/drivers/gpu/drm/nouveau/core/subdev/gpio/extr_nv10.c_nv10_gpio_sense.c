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
struct nouveau_gpio {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int nv_rd32 (struct nouveau_gpio*,int) ; 

__attribute__((used)) static int
nv10_gpio_sense(struct nouveau_gpio *gpio, int line)
{
	if (line < 2) {
		line = line * 16;
		line = nv_rd32(gpio, 0x600818) >> line;
		return !!(line & 0x0100);
	} else
	if (line < 10) {
		line = (line - 2) * 4;
		line = nv_rd32(gpio, 0x60081c) >> line;
		return !!(line & 0x04);
	} else
	if (line < 14) {
		line = (line - 10) * 4;
		line = nv_rd32(gpio, 0x600850) >> line;
		return !!(line & 0x04);
	}

	return -EINVAL;
}